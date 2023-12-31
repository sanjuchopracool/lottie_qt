#ifndef SOLIDCOMPOSITIONLAYER_H
#define SOLIDCOMPOSITIONLAYER_H

#include "base_composition_layer.h"

namespace  eao {

class SolidLayer;
class ShapeItem;

class SolidCompositionLayer : public BaseCompositionLayer
{
public:
    SolidCompositionLayer(const SolidLayer &solid_layer);
    void draw_layer(QPainter *painter, int parent_alpha) override;

private:
    const SolidLayer &m_layer;
};

}
#endif // SOLIDCOMPOSITIONLAYER_H
