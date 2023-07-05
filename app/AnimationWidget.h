#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <memory>
#include <QSettings>
#include <QWidget>

class QListWidget;
class QListWidgetItem;

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

private:
    void resize_animation(const QSize &size);
signals:
    void animation_loaded(const Composition *comp);

public slots:
    void slot_frame_changed(int frame);
    void layer_checked(QString, bool);

private:
    std::unique_ptr<Composition> m_composition;
    std::unique_ptr<AnimationContainer> m_animation_container;
    bool m_forced_update = false;
    int m_current_frame = 0;
};


class AnimationViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationViewWidget(QWidget *parent = nullptr);
    ~AnimationViewWidget();

private slots:
    void slot_animation_loaded(const Composition *comp);
    void item_changed(QListWidgetItem *item);

protected:
    QSize sizeHint() const override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void load(const QString &file);

private:
    AnimationWidget* m_animation_widget = nullptr;
    TimeLineWidget* m_timeline_widget = nullptr;
    QSettings m_settings;
    QListWidget *m_layers_view = nullptr;
};

} // namespace eao

#endif // ANIMATIONWIDGET_H
