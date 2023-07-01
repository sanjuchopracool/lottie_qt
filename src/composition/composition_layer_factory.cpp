#include "composition_layer_factory.h"

#include "model/layers/layer.h"
#include "model/layers/shape_layer.h"
#include "model/layers/solid_layer.h"

#include "null_composition_layer.h"
#include "base_composition_layer.h"
#include "shape_composition_layer.h"
#include "solid_composition_layer.h"

namespace  eao {

std::unique_ptr<BaseCompositionLayer> CompositionLayerFactory::composition_layer(const Layer &model)
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
