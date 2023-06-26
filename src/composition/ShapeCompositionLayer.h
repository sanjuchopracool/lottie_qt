#ifndef SHAPECOMPOSITIONLAYER_H
#define SHAPECOMPOSITIONLAYER_H

#include "AnimationNodes/ShapeNodeInterface.h"
#include "base_composition_layer.h"
#include <memory>
#include <vector>

namespace  eao {
class ShapeLayer;
class ShapeItem;

class ShapeCompositionLayer : public BaseCompositionLayer
{
public:
    ShapeCompositionLayer(const ShapeLayer &layer);

protected:
    void draw_layer(QPainter *painter, int alpha) override;

private:
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
};

}
#endif // SHAPECOMPOSITIONLAYER_H
