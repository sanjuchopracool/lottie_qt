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
    void setFrameInfo(float in_point,
                      float out_point,
                      float framerate);

private slots:
    void toggle_timeline();
    void slot_frame_changed(int);
    void slot_reset();

    void slot_slider_value_changed(int);

signals:
    void frameChanged(int);

private:
    Ui::TimeLineWidget *ui;
    QTimeLine m_timeline;
};

} //eao

#endif // TIMELINE_WIDGET_H
