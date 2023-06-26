#include "solid_composition_layer.h"

#include "Model/Layers/solid_layer.h"
#include "AnimationNodes/TransformationNode.h"
#include "AnimationNodes/AnimationNodeFactory.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
SolidCompositionLayer::SolidCompositionLayer(const SolidLayer *layer, const PaintBufferInfo &info)
    : TransformedPaintBuffer(layer->m_transform, info, layer),
    m_shape_layer(layer)
{
}

bool SolidCompositionLayer::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    if (m_transformation->need_update(t))
        return true;

    return false;
}

bool SolidCompositionLayer::update(FrameType t, bool force_update)
{
    if ((not force_update) and (not m_layer_model->in_range(t)))
        return false;

    bool render = force_update or need_update(t);
    if (render)
    {
        auto painter = TransformedPaintBuffer::painter(t);
        painter->setBrush(m_shape_layer->m_color);
        painter->drawRect(QRectF(0, 0, m_shape_layer->m_width, m_shape_layer->m_height));
    }

    return render;
}

}
