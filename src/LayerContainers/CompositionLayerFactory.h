#ifndef ANIMATIONLAYERFACTORY_H
#define ANIMATIONLAYERFACTORY_H

#include <memory>

namespace  Lottie {
class TransformedPaintBuffer;
class LayerModel;
struct PaintBufferInfo;

class CompositionLayerFactory
{
public:
static std::unique_ptr<TransformedPaintBuffer> composition_layer(const LayerModel* model, const PaintBufferInfo& info);
};

}

#endif // ANIMATIONLAYERFACTORY_H
