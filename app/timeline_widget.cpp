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


TimeLineWidget::TimeLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineWidget)
{
    ui->setupUi(this);
    m_timeline.setEasingCurve(QEasingCurve::Linear);
    connect(&m_timeline, SIGNAL(frameChanged(int)),
            this, SIGNAL(frameChanged(int)));
    connect(&m_timeline, SIGNAL(frameChanged(int)),
            this, SLOT(slot_frame_changed(int)));

    setFixedHeight(minimumSizeHint().height());
    connect(ui->pb_play, &QPushButton::clicked,
            this, &TimeLineWidget::toggle_timeline);
    connect(ui->pb_reset, &QPushButton::clicked,
            this, &TimeLineWidget::slot_reset);
    connect(ui->slider_progress, &QSlider::valueChanged,
            this, &TimeLineWidget::slot_slider_value_changed);
    connect(ui->spnbox_current, &QSpinBox::valueChanged,
            this, &TimeLineWidget::slot_slider_value_changed);
}

TimeLineWidget::~TimeLineWidget()
{
    delete ui;
}

void TimeLineWidget::setFrameInfo(float in_point, float out_point, float framerate)
{
    m_timeline.setStartFrame(in_point * 1000);
    m_timeline.setEndFrame(out_point * 1000);
    m_timeline.setDuration(
        ms_for_frame(framerate,
                     (out_point - in_point)));
    m_timeline.setUpdateInterval(20);
    m_timeline.setLoopCount(0);
    m_timeline.start();

    qDebug() << m_timeline.startFrame() << m_timeline.endFrame() << m_timeline.updateInterval()
             << m_timeline.duration();
    ui->lbl_totalFrames->setText(QString::number((int)out_point));
    ui->spnbox_current->setRange(in_point, out_point);
    ui->slider_progress->setRange(in_point, out_point);
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
    QSignalBlocker bl1(ui->slider_progress);
    QSignalBlocker bl2(ui->spnbox_current);
    int value = t/1000;
    ui->spnbox_current->setValue(value);
    ui->slider_progress->setValue(value);
}

void TimeLineWidget::slot_reset()
{
    m_timeline.setCurrentTime(0);
}

void TimeLineWidget::slot_slider_value_changed(int value)
{
    m_timeline.setCurrentTime((m_timeline.duration()*value)/(ui->slider_progress->maximum() - ui->slider_progress->minimum()));
}


}
