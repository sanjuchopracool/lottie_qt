#include "timeline_widget.h"
#include "ui_timelinewidget.h"
#include <QSignalBlocker>

namespace eao {

namespace {
int ms_for_frame(double frame_rate, double in_value)
{
    return (1000.0 / frame_rate) * in_value;
}

//double frame_for_ms(double frame_rate, int in_value)
//{
//    return (frame_rate * in_value / 1000);
//}
} // namespace

TimeLineWidget::TimeLineWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::TimeLineWidget)
{
    m_ui->setupUi(this);
    m_timeline.setEasingCurve(QEasingCurve::Linear);
    connect(&m_timeline, SIGNAL(frameChanged(int)), this, SIGNAL(frame_changed(int)));
    connect(&m_timeline, SIGNAL(frameChanged(int)), this, SLOT(slot_frame_changed(int)));

    setFixedHeight(minimumSizeHint().height());
    connect(m_ui->pb_play, &QPushButton::clicked, this, &TimeLineWidget::toggle_timeline);
    connect(m_ui->pb_reset, &QPushButton::clicked, this, &TimeLineWidget::slot_reset);
    connect(m_ui->slider_progress,
            &QSlider::valueChanged,
            this,
            &TimeLineWidget::slot_slider_value_changed);
    connect(m_ui->spnbox_current,
            &QSpinBox::valueChanged,
            this,
            &TimeLineWidget::slot_slider_value_changed);
}

TimeLineWidget::~TimeLineWidget()
{
    delete m_ui;
}

void TimeLineWidget::set_frame_info(float in_point, float out_point, float framerate)
{
    m_timeline.setStartFrame(in_point * 1000);
    m_timeline.setEndFrame(out_point * 1000);
    m_timeline.setDuration(ms_for_frame(framerate, (out_point - in_point)));
    m_timeline.setUpdateInterval(20);
    m_timeline.setLoopCount(0);
    //    m_timeline.start();

    qDebug() << m_timeline.startFrame() << m_timeline.endFrame() << m_timeline.updateInterval()
             << m_timeline.duration();
    m_ui->lbl_totalFrames->setText(QString::number((int) out_point));
    m_ui->spnbox_current->setRange(in_point, out_point);
    m_ui->slider_progress->setRange(in_point, out_point);
}

void TimeLineWidget::toggle_timeline()
{
    if (m_timeline.state() == QTimeLine::Running)
        m_timeline.stop();
    else
        m_timeline.resume();
}

void TimeLineWidget::slot_frame_changed(int t)
{
    QSignalBlocker bl1(m_ui->slider_progress);
    QSignalBlocker bl2(m_ui->spnbox_current);
    int value = t / 1000;
    m_ui->spnbox_current->setValue(value);
    m_ui->slider_progress->setValue(value);
}

void TimeLineWidget::slot_reset()
{
    m_timeline.setCurrentTime(0);
}

void TimeLineWidget::slot_slider_value_changed(int value)
{
    m_timeline.setCurrentTime(
        (m_timeline.duration() * value)
        / (m_ui->slider_progress->maximum() - m_ui->slider_progress->minimum()));
}

} // namespace eao
