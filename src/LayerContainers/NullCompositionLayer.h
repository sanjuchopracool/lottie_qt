#ifndef NULLCOMPOSITIONLAYER_H
#define NULLCOMPOSITIONLAYER_H

#include "TransformedPaintBuffer.h"

namespace Lottie {
class LayerModel;

class NullCompositionLayer : public TransformedPaintBuffer
{
public:
    NullCompositionLayer(const LayerModel *layer, const PaintBufferInfo &info);
};

}

#endif // NULLCOMPOSITIONLAYER_H
