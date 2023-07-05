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
#include <QHBoxLayout>
#include <QJsonObject>
#include <QListWidget>
#include <QListWidgetItem>
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
        emit animation_loaded(m_composition.get());
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
    painter.fillRect(this->rect(), Qt::black);
    qreal inverse_pixel_ratio = 1.0 / devicePixelRatioF();
    painter.scale(inverse_pixel_ratio, inverse_pixel_ratio);
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

void AnimationWidget::layer_checked(QString layer_name, bool visible)
{
    for (const auto &layer : m_animation_container->layers()) {
        if (layer->name() == layer_name) {
            layer->set_debug_visible(visible);
            //            m_animation_container->update(m_current_frame, true);
            update();
        }
    }
}

AnimationViewWidget::AnimationViewWidget(QWidget *parent)
    : m_settings("chops", "app", this)
{
    QHBoxLayout *main_layout = new QHBoxLayout();
    QVBoxLayout *v_layout = new QVBoxLayout();
    m_animation_widget = new AnimationWidget();
    m_timeline_widget = new TimeLineWidget();
    m_layers_view = new QListWidget(this);
    m_layers_view->setFixedWidth(150);
    v_layout->addWidget(m_animation_widget);
    v_layout->addWidget(m_timeline_widget);
    main_layout->addLayout(v_layout);
    main_layout->addWidget(m_layers_view);
    setLayout(main_layout);

    connect(m_timeline_widget,
            &TimeLineWidget::frame_changed,
            m_animation_widget,
            &AnimationWidget::slot_frame_changed);

    connect(m_animation_widget,
            &AnimationWidget::animation_loaded,
            this,
            &AnimationViewWidget::slot_animation_loaded);

    connect(m_layers_view, &QListWidget::itemChanged, this, &AnimationViewWidget::item_changed);

    auto last_file_opened = m_settings.value(last_file_key).toString();
    load(last_file_opened);
}

AnimationViewWidget::~AnimationViewWidget() {}

void AnimationViewWidget::slot_animation_loaded(const Composition *comp)
{
    QSize size;
    m_animation_widget->resize(comp->width(), comp->height());
    size.setWidth(
        std::max(comp->width() + m_layers_view->width(), m_timeline_widget->minimumWidth()));
    size.setHeight(comp->height() + m_timeline_widget->minimumHeight());
    resize(size);

    m_timeline_widget->set_frame_info(comp->in_point(), comp->out_point(), comp->framerate());

    // set list items
    m_layers_view->clear();
    QSignalBlocker blk(m_layers_view);
    const Composition::LayerList &layers = comp->layers();
    for (int i = 0; i < layers.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(layers[i]->name());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Checked);
        m_layers_view->addItem(item);
    }
}

void AnimationViewWidget::item_changed(QListWidgetItem *item)
{
    m_animation_widget->layer_checked(item->text(), item->checkState() == Qt::Checked);
}

QSize AnimationViewWidget::sizeHint() const
{
    QSize size = m_animation_widget->minimumSizeHint();
    size.setWidth(size.width() + m_layers_view->minimumWidth());
    size.setHeight(size.height() + m_timeline_widget->height());
    return size;
}

void AnimationViewWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() & Qt::ControlModifier) and (event->key() == Qt::Key_O)) {
        QFileInfo fileInfo(m_settings.value(last_file_key).toString());
        QString file_path = QFileDialog::getOpenFileName(this,
                                                         "select file",
                                                         fileInfo.dir().path(),
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
