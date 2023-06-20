#ifndef SHAPECOMPOSITIONLAYER_H
#define SHAPECOMPOSITIONLAYER_H

#include "TransformedPaintBuffer.h"
#include "AnimationNodes/ShapeNodeInterface.h"
#include <vector>
#include <memory>

namespace  Lottie {
class ShapeLayer;
class ShapeItem;

class ShapeCompositionLayer : public TransformedPaintBuffer
{
public:
    ShapeCompositionLayer(const ShapeLayer *layer, const PaintBufferInfo &info);

    bool update(FrameType t, bool force_update) override;

protected:
    bool need_update(FrameType t) const override;

private:
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
};

}
#endif // SHAPECOMPOSITIONLAYER_H
