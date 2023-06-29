#include "base_composition_layer.h"
#include "AnimationNodes/TransformationNode.h"
#include "Model/Layers/layer.h"
#include "Utility/Primitives/Transformation.h"

#include <QDebug>
#include <QPainter>


namespace eao {

BaseCompositionLayer::BaseCompositionLayer(const Layer &layer_model)
    : m_layer_model(layer_model)
    , m_transformation(std::make_unique<LayerTransformationNode>(layer_model.m_transform))
{
    m_transformation->set_listener(this);
}

BaseCompositionLayer::~BaseCompositionLayer() {}

FrameType BaseCompositionLayer::local_frame(FrameType t) const
{
    return t;
}

void BaseCompositionLayer::draw(QPainter *painter, int alpha)
{
    if (m_layer_model.m_hidden)
        return;

    painter->save();
    painter->setTransform(m_transformation->tranform(), true);
    draw_layer(painter, alpha);
    painter->restore();
}

void BaseCompositionLayer::update(FrameType t, bool force_update)
{
    // TODO check hidden layer
    m_dirty = false;
    m_transformation->update(t, force_update);
}

QTransform BaseCompositionLayer::transform() const
{
    return m_transformation->tranform();
}

int BaseCompositionLayer::opacity() const
{
    return m_transformation->opacity();
}

} // namespace eao
