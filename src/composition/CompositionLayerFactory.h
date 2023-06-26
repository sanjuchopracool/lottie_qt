#ifndef ANIMATIONLAYERFACTORY_H
#define ANIMATIONLAYERFACTORY_H

#include <memory>

namespace  eao {
class BaseCompositionLayer;
class LayerModel;
struct PaintBufferInfo;

class CompositionLayerFactory
{
public:
    static std::unique_ptr<BaseCompositionLayer> composition_layer(const LayerModel &model);
};

}

#endif // ANIMATIONLAYERFACTORY_H
