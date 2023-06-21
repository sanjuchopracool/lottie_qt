#include "CompositionLayerFactory.h"

#include "../Model/Layers/LayerModel.h"
#include "../Model/Layers/ShapeLayer.h"
#include "../Model/Layers/solid_layer.h"

#include "TransformedPaintBuffer.h"
#include "ShapeCompositionLayer.h"
#include "NullCompositionLayer.h"
#include "solid_composition_layer.h"

namespace  eao {

std::unique_ptr<TransformedPaintBuffer> CompositionLayerFactory::composition_layer(const LayerModel *model, const PaintBufferInfo &info)
{
    std::unique_ptr<TransformedPaintBuffer> layer;
    switch (model->m_type) {
    case LayerType::Shape:
        layer = std::make_unique<ShapeCompositionLayer>(static_cast<const ShapeLayer*>(model), info);
        break;
    case LayerType::Null:
        layer = std::make_unique<NullCompositionLayer>(model, info);
        break;
    case LayerType::Solid:
        layer = std::make_unique<SolidCompositionLayer>(static_cast<const SolidLayer*>(model), info);
        break;
    default:
        assert(false);
        break;
    }

    return layer;
}

}
