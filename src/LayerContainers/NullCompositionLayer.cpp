#include "NullCompositionLayer.h"

#include "Model/Layers/ShapeLayer.h"
#include "AnimationNodes/TransformationNode.h"

namespace eao {

NullCompositionLayer::NullCompositionLayer(const LayerModel *layer, const PaintBufferInfo &info)
    : TransformedPaintBuffer(layer->m_transform, info, layer)
{

}

}
