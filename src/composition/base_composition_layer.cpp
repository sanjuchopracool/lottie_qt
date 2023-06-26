#include "base_composition_layer.h"
#include "AnimationNodes/TransformationNode.h"
#include "Model/Layers/LayerModel.h"
#include "Utility/Primitives/Transformation.h"

#include <QDebug>
#include <QPainter>


namespace eao {

BaseCompositionLayer::BaseCompositionLayer(const LayerModel &layer_model)
    : m_layer_model(layer_model)
    , m_transformation(std::make_unique<TransformationNode3D>(layer_model.m_transform))
{}

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
    painter->setTransform(m_transformation->tranform());
    draw_layer(painter, alpha);
    painter->restore();
}

void BaseCompositionLayer::update(FrameType t, bool force_update)
{
    m_transformation->update(t, force_update);
}

} // namespace eao
