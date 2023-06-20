#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QTimeLine>

#include <memory>

namespace Lottie {
class Animation;
class AnimationContainer;

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
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent* ev) override;

private slots:
    void on_frame_changed(int frame);

private:
    std::unique_ptr<Animation> m_animation;
    std::unique_ptr<AnimationContainer> m_animation_container;
    QTimeLine m_timeline;
    bool m_forced_update = false;

};

}

#endif // ANIMATIONWIDGET_H
