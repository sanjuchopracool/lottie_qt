#include "AnimationWidget.h"
#include <LayerContainers/AnimationContainer.h>
#include <Model/composition.h>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QPainter>

#include <AutoProfiler.h>
#include <QJsonObject>
#include <QVBoxLayout>
#include "timeline_widget.h"

namespace eao {

AnimationWidget::AnimationWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200,200);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

AnimationWidget::~AnimationWidget() {}

bool AnimationWidget::load(const QString &file_path)
{
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        m_composition = std::make_unique<Composition>();
        QStringList messages;
        QJsonObject obj = doc.object();
        m_composition->decode(obj, messages);
        for(const auto& message : messages)
            qDebug() << message;

        m_animation_container = std::make_unique<AnimationContainer>(m_composition.get());
        m_forced_update = true;
        emit animation_loaded(QSize(m_composition->m_width, m_composition->m_height),
                              m_composition->m_in_point,
                              m_composition->m_out_point,
                              m_composition->m_framerate);
        return true;
    }
    return false;
}

QSize AnimationWidget::sizeHint() const
{
    if (m_composition)
        return QSize(m_composition->m_width, m_composition->m_height);
    return QSize(350, 350);
}

void AnimationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    //    painter.fillRect(this->rect(), Qt::darkGreen);
    if (m_animation_container) {
        //        AutoProfiler p("D");
        m_animation_container->draw(&painter);
    }
}

void AnimationWidget::resizeEvent(QResizeEvent *ev)
{
    auto size = ev->size();
    if (m_animation_container) {
        m_animation_container->resize(size.width(), size.height());
        m_forced_update = true;
    }
}

void AnimationWidget::on_frame_changed(int time)
{
//    static int counter = 1;
    FrameType t = static_cast<FrameType>(time) / 1000.0;
//    qDebug() << t << counter++;
    if (m_animation_container) {
        //        AutoProfiler p("U");
        if (m_animation_container->update(t, m_forced_update))
            this->update();

        m_forced_update = false;
    }
}

AnimationViewWidget::AnimationViewWidget(QWidget *parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    m_animation_widget = new AnimationWidget();
    m_timeline_widget = new TimeLineWidget();
    mainLayout->addWidget(m_animation_widget);
    mainLayout->addWidget(m_timeline_widget);
    setLayout(mainLayout);

    connect(m_timeline_widget, SIGNAL(frameChanged(int)),
            m_animation_widget, SLOT(on_frame_changed(int)));

    connect(m_animation_widget, SIGNAL(animation_loaded(QSize,float,float,float)),
            this, SLOT(slot_animation_loaded(QSize,float,float,float)));

    m_animation_widget->load(QDir::home().absolutePath() + "/Downloads/skia_repeater.json");
}

AnimationViewWidget::~AnimationViewWidget()
{

}

void AnimationViewWidget::slot_animation_loaded(QSize size, float in_point,
                                                float out_point, float framerate)
{
    size.setWidth(std::max(size.width(), m_timeline_widget->width()));
    size.setHeight(size.height() + m_timeline_widget->height());
    resize(size);

    m_timeline_widget->setFrameInfo(in_point, out_point, framerate);
}

QSize AnimationViewWidget::sizeHint() const
{
    QSize size = m_animation_widget->minimumSizeHint();
    size.setHeight(size.height() + m_timeline_widget->height());
    return size;
}

void AnimationViewWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_O)) {
        QString file_path = QFileDialog::getOpenFileName(this,
                                                         "select file",
                                                         QDir::homePath() + "/Downloads",
                                                         "*.json");
        m_animation_widget->load(file_path);
    }
}

} // namespace eao
