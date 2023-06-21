#include "AnimationContainer.h"
#include "../Model/Animation.h"
#include "CompositionLayerFactory.h"

#include <algorithm>
#include <QDebug>
#include <QMap>
#include <QPainter>

namespace eao {

AnimationContainer::AnimationContainer(const Animation *animation)
    : m_animation(animation)
    , m_buffer_info(PaintBufferInfo(QSize(animation->m_width, animation->m_height), 1, 1))
{
    load_layers();
    on_resize();
}

AnimationContainer::~AnimationContainer() {}

void AnimationContainer::draw(QPainter *painter)
{
    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
        (*it)->draw(painter, m_last_updated_frame);
}

bool AnimationContainer::update(FrameType t, bool force_update)
{
    m_last_updated_frame = t;
    bool result = false;
    for (const auto &layer : m_layers) {
        if (layer->update(layer->local_frame(t), force_update))
            result = true;
    }
    return result;
}

void AnimationContainer::resize(int x, int y)
{
    double an_width = m_animation->m_width;
    double an_height = m_animation->m_height;

    int h = (an_height / an_width) * x;
    int w = 0;
    qreal scale;
    if (h > y) {
        h = y;
        scale = h / an_height;
        w = (an_width / an_height) * y;
    } else {
        w = x;
        scale = w / an_width;
    }
    m_buffer_info.m_size = QSize(w, h);
    m_buffer_info.m_scale_x = scale;
    m_buffer_info.m_scale_y = scale;

    on_resize();
}

void AnimationContainer::on_resize()
{
    for (auto &layer : m_layers) {
        layer->update_buffer_info(m_buffer_info);
    }
}

void AnimationContainer::load_layers()
{
    QMap<int, int> index_to_parent;
    QMap<int, int> model_index_to_index;
    int i = 0;
    for (const auto &layer : m_animation->m_layers) {
        m_layers.emplace_back(CompositionLayerFactory::composition_layer(layer, m_buffer_info));
        if (layer->m_parent_index >= 0)
            index_to_parent[i] = layer->m_parent_index;
        model_index_to_index[layer->m_index] = i;
        i++;
    }

    for (const auto &child_layer_index : index_to_parent.keys()) {
        int parent_index = index_to_parent.value(child_layer_index);
        int parent_layer_index = model_index_to_index.value(parent_index, -1);
        if (parent_layer_index != -1 and parent_layer_index < m_layers.size()) {
            m_layers[child_layer_index]->set_parent_transform(
                m_layers[parent_layer_index]->transform());
        }
    }
    //    std::reverse(m_layers.begin(), m_layers.end());
}
} // namespace eao
