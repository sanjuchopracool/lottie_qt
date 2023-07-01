#include "AnimationWidget.h"
#include "parser/lottie/composition_parser.h"
#include <composition/animation_container.h>
#include <model/composition.h>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QPainter>

#include "timeline_widget.h"
#include <profiler.h>
#include <QJsonObject>
#include <QVBoxLayout>

namespace eao {

const QStringView last_file_key(u"last_file");

AnimationWidget::AnimationWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

AnimationWidget::~AnimationWidget() {}

bool AnimationWidget::load(const QString &file_path)
{
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QStringList messages;
        QJsonObject obj = doc.object();
        m_composition = eao::Lottie::LottieParser::parse(obj, messages);
        for (const auto &message : messages)
            qDebug() << message;

        m_animation_container = std::make_unique<AnimationContainer>(m_composition.get());
        m_forced_update = true;
        emit animation_loaded(QSize(m_composition->width(), m_composition->height()),
                              m_composition->in_point(),
                              m_composition->out_point(),
                              m_composition->framerate());
        m_forced_update = true;
        resize_animation(this->size());
        return true;
    }
    return false;
}

QSize AnimationWidget::sizeHint() const
{
    if (m_composition)
        return QSize(m_composition->width(), m_composition->height());
    return QSize(350, 350);
}

void AnimationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    qreal inverse_pixel_ratio = 1.0 / devicePixelRatioF();
    painter.scale(inverse_pixel_ratio, inverse_pixel_ratio);
    //    painter.fillRect(this->rect(), Qt::darkGreen);
    if (m_animation_container) {
        //        AutoProfiler p("D");
        m_animation_container->draw(&painter);
    }
}

void AnimationWidget::resizeEvent(QResizeEvent *ev)
{
    auto size = ev->size();
    resize_animation(size);
}

void AnimationWidget::resize_animation(const QSize &size)
{
    if (m_animation_container) {
        qreal pixel_ratio = devicePixelRatioF();
        m_animation_container->resize(pixel_ratio * size.width(), pixel_ratio * size.height());
        m_forced_update = true;
        slot_frame_changed(m_current_frame);
    }
}

void AnimationWidget::slot_frame_changed(int time)
{
    m_current_frame = time;
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
    : m_settings("chops", "app", this)
{
    QVBoxLayout *main_layout = new QVBoxLayout();
    m_animation_widget = new AnimationWidget();
    m_timeline_widget = new TimeLineWidget();
    main_layout->addWidget(m_animation_widget);
    main_layout->addWidget(m_timeline_widget);
    setLayout(main_layout);

    connect(m_timeline_widget,
            &TimeLineWidget::frame_changed,
            m_animation_widget,
            &AnimationWidget::slot_frame_changed);

    connect(m_animation_widget,
            &AnimationWidget::animation_loaded,
            this,
            &AnimationViewWidget::slot_animation_loaded);

    auto last_file_opened = m_settings.value(last_file_key).toString();
    load(last_file_opened);
}

AnimationViewWidget::~AnimationViewWidget() {}

void AnimationViewWidget::slot_animation_loaded(QSize size,
                                                float in_point,
                                                float out_point,
                                                float framerate)
{
    size.setWidth(std::max(size.width(), m_timeline_widget->width()));
    size.setHeight(size.height() + m_timeline_widget->height());
    resize(size);

    m_timeline_widget->set_frame_info(in_point, out_point, framerate);
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
        m_settings.setValue(last_file_key, file_path);
        load(file_path);
    }
}

void AnimationViewWidget::load(const QString &file)
{
    m_animation_widget->load(file);
    setWindowTitle(file);
}

} // namespace eao
