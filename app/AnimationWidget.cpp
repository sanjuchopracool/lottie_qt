#include "AnimationWidget.h"
#include <LayerContainers/AnimationContainer.h>
#include <Model/Animation.h>

#include <QFile>
#include <QJsonDocument>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>

#include <AutoProfiler.h>

namespace {
int ms_for_frame(double frame_rate, double in_value)
{
    return (1000.0/frame_rate)*in_value;
}

double frame_for_ms(double frame_rate, int in_value)
{
    return (frame_rate*in_value/1000);
}
}

namespace eao {

AnimationWidget::AnimationWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    m_timeline.setEasingCurve(QEasingCurve::Linear);
    connect(&m_timeline, SIGNAL(frameChanged(int)), this, SLOT(on_frame_changed(int)));
    load(QDir::home().absolutePath() + "/Downloads/PLANE.json");
}

AnimationWidget::~AnimationWidget()
{

}

bool AnimationWidget::load(const QString &file_path)
{
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        m_animation = std::make_unique<Animation>();
        m_animation->decode(doc.object());

        m_animation_container = std::make_unique<AnimationContainer>(m_animation.get());

        m_timeline.setStartFrame(m_animation->m_start_frame * 1000);
        m_timeline.setEndFrame(m_animation->m_end_frame * 1000);
        m_timeline.setDuration(
            ms_for_frame(m_animation->m_frame_rate,
                         (m_animation->m_end_frame - m_animation->m_start_frame)));
        m_timeline.setUpdateInterval(20);
        m_timeline.setLoopCount(0);
        m_timeline.start();

        qDebug() << m_timeline.startFrame() << m_timeline.endFrame() << m_timeline.updateInterval() << m_timeline.duration();
        m_forced_update = true;
//        on_frame_changed(0);
        resize(m_animation->m_width, m_animation->m_height);
        return true;
    }
    return false;
}

QSize AnimationWidget::sizeHint() const
{
    if (m_animation)
        return QSize(m_animation->m_width, m_animation->m_height);
    return QSize(350, 350);
}

void AnimationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    //    painter.fillRect(this->rect(), Qt::darkGreen);
    if (m_animation_container)
    {
//        AutoProfiler p("D");
        m_animation_container->draw(&painter);
    }
}

void AnimationWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_O))
    {
        QString file_path = QFileDialog::getOpenFileName(this, "select file", QDir::homePath() + "/Downloads",
                                                         "*.json");
        load(file_path);
    }
}

void AnimationWidget::resizeEvent(QResizeEvent *ev)
{
    auto size = ev->size();
    if (m_animation_container)
    {
        m_animation_container->resize(size.width(), size.height());
        m_forced_update = true;
    }
}

void AnimationWidget::on_frame_changed(int time)
{
    static int counter = 1;
    FrameType t = static_cast<FrameType>(time) / 1000.0;
    qDebug() << t << counter++;
    if (m_animation_container) {
        //        AutoProfiler p("U");
        if (m_animation_container->update(t, m_forced_update))
            this->update();

        m_forced_update = false;
    }
}

} // namespace eao
