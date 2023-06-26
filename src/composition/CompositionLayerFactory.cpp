#include "CompositionLayerFactory.h"

#include "Model/Layers/layer.h"
#include "Model/Layers/ShapeLayer.h"
#include "Model/Layers/solid_layer.h"

#include "NullCompositionLayer.h"
#include "ShapeCompositionLayer.h"
#include "base_composition_layer.h"
#include "solid_composition_layer.h"

namespace  eao {

std::unique_ptr<BaseCompositionLayer> CompositionLayerFactory::composition_layer(
    const Layer &model)
{
    std::unique_ptr<BaseCompositionLayer> layer;
    switch (model.m_type) {
    case LayerType::Shape:
        layer = std::make_unique<ShapeCompositionLayer>(static_cast<const ShapeLayer &>(model));
        break;
    case LayerType::Null:
        layer = std::make_unique<NullCompositionLayer>(model);
        break;
    case LayerType::Solid:
        layer = std::make_unique<SolidCompositionLayer>(static_cast<const SolidLayer &>(model));
        break;
    default:
        assert(false);
        break;
    }

    return layer;
}

}
