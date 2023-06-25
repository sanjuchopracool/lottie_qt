#ifndef TIMELINE_WIDGET_H
#define TIMELINE_WIDGET_H

#include <QWidget>
#include <QTimeLine>

namespace Ui {
class TimeLineWidget;
}
namespace eao {

class TimeLineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeLineWidget(QWidget *parent = nullptr);
    ~TimeLineWidget();
    void set_frame_info(float in_point, float out_point, float framerate);

private slots:
    void toggle_timeline();
    void slot_frame_changed(int);
    void slot_reset();

    void slot_slider_value_changed(int);

signals:
    void frame_changed(int);

private:
    Ui::TimeLineWidget *m_ui;
    QTimeLine m_timeline;
};

} //eao

#endif // TIMELINE_WIDGET_H
