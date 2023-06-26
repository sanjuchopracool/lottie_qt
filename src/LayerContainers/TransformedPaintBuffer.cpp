#include "TransformedPaintBuffer.h"
#include "AnimationNodes/TransformationNode.h"

#include "Model/Layers/LayerModel.h"
#include "Utility/Primitives/Transformation.h"

#include <QPainter>
#include <QDebug>

namespace eao {

TransformedPaintBuffer::TransformedPaintBuffer(const Transformation3D& transformation, const PaintBufferInfo &info, const LayerModel *layer_mode)
    : CompositionLayer(info),
      m_layer_model(layer_mode),
    m_transformation(std::make_unique<TransformationNode3D>(transformation))
{
    m_is_static = m_transformation->is_static();
}

TransformedPaintBuffer::~TransformedPaintBuffer()
{

}

void TransformedPaintBuffer::draw(QPainter *painter, FrameType t) const
{
    if(m_layer_model->m_hidden)
        return;

    if (m_layer_model->in_range(t))
        PaintBuffer::draw(painter, t);
}

bool TransformedPaintBuffer::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_transformation->update_transform(t);
    }

    return result;
}

void TransformedPaintBuffer::set_parent_transform(const TransformationNode3D *parent_transform)
{
    m_transformation->set_parent_transform(parent_transform);
}

FrameType TransformedPaintBuffer::local_frame(FrameType t) const
{
    return t;
}

bool TransformedPaintBuffer::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_transformation->need_update(t);
}

std::unique_ptr<QPainter> TransformedPaintBuffer::painter(FrameType t)
{
    auto painter = CompositionLayer::painter(t);
    m_transformation->update(t, painter.get());
    return painter;
}
}
