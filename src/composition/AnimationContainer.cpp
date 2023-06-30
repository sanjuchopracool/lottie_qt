#include "AnimationContainer.h"
#include "CompositionLayerFactory.h"
#include "Model/Layers/layer.h"
#include "Model/composition.h"

#include <algorithm>
#include <QDebug>
#include <QMap>
#include <QPainter>

namespace eao {

AnimationContainer::AnimationContainer(const Composition *animation)
    : m_animation(animation)
{
    load_layers();
    on_resize();
}

AnimationContainer::~AnimationContainer() {}

void AnimationContainer::draw(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->scale(m_scale_x, m_scale_y);
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
        (*it)->draw(painter, 255);
}

bool AnimationContainer::update(FrameType t, bool force_update)
{
    m_dirty = false;
    m_last_updated_frame = t;
    for (const auto &layer : m_layers) {
        layer->update_layer(layer->local_frame(t), force_update);
    }
    return m_dirty;
}

void AnimationContainer::resize(int x, int y)
{
    double width = m_animation->width();
    double height = m_animation->height();

    int h = (height / width) * x;
    int w = 0;
    qreal scale;
    if (h > y) {
        h = y;
        scale = h / height;
        w = (width / height) * y;
    } else {
        w = x;
        scale = w / width;
    }
    m_size = QSize(w, h);
    m_scale_x = scale;
    m_scale_y = scale;

    on_resize();
}

void AnimationContainer::on_resize()
{
    //    for (auto &layer : m_layers) {
    //        layer->update_buffer_info(m_buffer_info);
    //    }
}

void AnimationContainer::load_layers()
{
    QMap<int, int> index_to_parent;
    QMap<int, int> model_index_to_index;
    int i = 0;
    for (const auto &layer : m_animation->layers()) {
        m_layers.emplace_back(CompositionLayerFactory::composition_layer(*layer));
        m_layers.back()->add_listener(this);
        if (layer->m_parent_index >= 0)
            index_to_parent[i] = layer->m_parent_index;
        model_index_to_index[layer->m_index] = i;
        i++;
    }

    //    for (const auto &child_layer_index : index_to_parent.keys()) {
    //        int parent_index = index_to_parent.value(child_layer_index);
    //        int parent_layer_index = model_index_to_index.value(parent_index, -1);
    //        if (parent_layer_index != -1 and parent_layer_index < m_layers.size()) {
    //            //            m_layers[child_layer_index]->set_parent_transform(
    //            //                m_layers[parent_layer_index]->transform());
    //        }
    //    }
}

} // namespace eao
