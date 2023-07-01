#ifndef ANIMATIONLAYERFACTORY_H
#define ANIMATIONLAYERFACTORY_H

#include <memory>

namespace  eao {
class BaseCompositionLayer;
class Layer;
struct PaintBufferInfo;

class CompositionLayerFactory
{
public:
    static std::unique_ptr<BaseCompositionLayer> composition_layer(const Layer &model);
};

}

#endif // ANIMATIONLAYERFACTORY_H
