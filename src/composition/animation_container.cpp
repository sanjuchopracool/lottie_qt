#include "animation_container.h"
#include "composition_layer_factory.h"
#include "model/composition.h"
#include "model/layers/layer.h"

#include <algorithm>
#include <QDebug>
#include <unordered_map>
#include <QPainter>

namespace eao {

AnimationContainer::AnimationContainer(const Composition *animation)
    : m_animation(animation)
{
    load_layers();
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
}

void AnimationContainer::load_layers()
{
    std::unordered_map<int, int> local_index_to_parent_layer_index;
    std::unordered_map<int, int> layer_index_to_local_index;
    int i = 0;
    for (const auto &layer : m_animation->layers()) {
        m_layers.emplace_back(CompositionLayerFactory::composition_layer(*layer));
        m_layers.back()->add_listener(this);
        if (layer->m_parent_index >= 0)
            local_index_to_parent_layer_index[i] = layer->m_parent_index;
        layer_index_to_local_index[layer->m_index] = i;
        i++;
    }

    auto get_parent_local_index = [&](int child_layer_index) {
        auto it =  local_index_to_parent_layer_index.find(child_layer_index);
        if (it == local_index_to_parent_layer_index.end())
            return -1;

        int parent_layer_index = it->second;

        auto parent_it =  layer_index_to_local_index.find(parent_layer_index);
        if (parent_it == layer_index_to_local_index.end())
            return -1;

        return parent_it->second;
    };

    for (int i = 0; i < m_layers.size(); ++i) {
        std::vector<const BaseCompositionLayer*> parent_layers;
        int parent_local_index = get_parent_local_index(i);
        while (parent_local_index != -1 and parent_local_index < m_layers.size()) {
            parent_layers.insert(parent_layers.begin(), m_layers[parent_local_index].get());
            parent_local_index = get_parent_local_index(parent_local_index);
        }

        m_layers[i]->set_parent_layers(parent_layers);
    }
}

} // namespace eao
