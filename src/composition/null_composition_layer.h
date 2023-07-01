#ifndef NULLCOMPOSITIONLAYER_H
#define NULLCOMPOSITIONLAYER_H

#include "base_composition_layer.h"

namespace eao {
class Layer;

class NullCompositionLayer : public BaseCompositionLayer
{
public:
    NullCompositionLayer(const Layer &layer);

protected:
    void draw_layer(QPainter *painter, int alpha) override;
};

}

#endif // NULLCOMPOSITIONLAYER_H
