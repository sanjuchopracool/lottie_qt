#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>

#include <memory>

namespace eao {
class Composition;
class AnimationContainer;
class TimeLineWidget;

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(QWidget *parent = nullptr);
    ~AnimationWidget();

    bool load(const QString& file);

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *ev) override;

signals:
    void animation_loaded(QSize,
                          float in_point,
                          float out_point,
                          float framerate);

public slots:
    void slot_frame_changed(int frame);

private:
    std::unique_ptr<Composition> m_composition;
    std::unique_ptr<AnimationContainer> m_animation_container;
    bool m_forced_update = false;

};


class AnimationViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationViewWidget(QWidget *parent = nullptr);
    ~AnimationViewWidget();

private slots:
    void slot_animation_loaded(QSize size,
                               float in_point,
                               float out_point,
                               float framerate);
protected:
    QSize sizeHint() const override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    AnimationWidget* m_animation_widget = nullptr;
    TimeLineWidget* m_timeline_widget = nullptr;
};

} // namespace eao

#endif // ANIMATIONWIDGET_H
