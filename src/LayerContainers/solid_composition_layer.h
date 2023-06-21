#ifndef SOLIDCOMPOSITIONLAYER_H
#define SOLIDCOMPOSITIONLAYER_H

#include "TransformedPaintBuffer.h"
#include "AnimationNodes/ShapeNodeInterface.h"
#include <vector>
#include <memory>

namespace  eao {
class SolidLayer;
class ShapeItem;

class SolidCompositionLayer : public TransformedPaintBuffer
{
public:
    SolidCompositionLayer(const SolidLayer *layer, const PaintBufferInfo &info);

    bool update(FrameType t, bool force_update) override;

protected:
    bool need_update(FrameType t) const override;

private:
    const SolidLayer *m_shape_layer;
};

}
#endif // SOLIDCOMPOSITIONLAYER_H
