#include "base_composition_layer.h"
#include "animation_nodes/transformation_node.h"
#include "model/layers/layer.h"
#include "utility/primitives/transformation.h"

#include <QDebug>
#include <QPainter>


namespace eao {

BaseCompositionLayer::BaseCompositionLayer(const Layer &layer_model)
    : m_layer_model(layer_model)
    , m_transformation(std::make_unique<LayerTransformationNode>(layer_model.m_transform))
{
    m_transformation->add_listener(this);
}

BaseCompositionLayer::~BaseCompositionLayer() {}

FrameType BaseCompositionLayer::local_frame(FrameType t) const
{
    return t;
}

void BaseCompositionLayer::draw(QPainter *painter, int alpha)
{
    if (m_layer_model.m_hidden || !m_visible)
        return;

    painter->save();
    for (const auto *layer : m_parents) {
        painter->setTransform(layer->transform(), true);
    }

    painter->setTransform(m_transformation->transform(), true);
    draw_layer(painter, alpha);
    painter->restore();
}

void BaseCompositionLayer::update_layer(FrameType t, bool force_update)
{
    // TODO check hidden layer or in range update
    // also start time
    bool visible = m_layer_model.in_range(t);
    if (m_visible != visible) {
        m_visible = visible;
        CascadeUpdateListener::on_update();
    }
    if (!m_visible)
        return;

    m_dirty = false;
    m_transformation->update(t, force_update);
}

QTransform BaseCompositionLayer::transform() const
{
    return m_transformation->transform();
}

int BaseCompositionLayer::opacity() const
{
    return m_transformation->opacity();
}

} // namespace eao
