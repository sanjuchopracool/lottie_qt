#ifndef NULLCOMPOSITIONLAYER_H
#define NULLCOMPOSITIONLAYER_H

#include "base_composition_layer.h"

namespace eao {
class LayerModel;

class NullCompositionLayer : public BaseCompositionLayer
{
public:
    NullCompositionLayer(const LayerModel &layer);

protected:
    void draw_layer(QPainter *painter, int alpha) override;
};

}

#endif // NULLCOMPOSITIONLAYER_H
