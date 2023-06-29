#ifndef SHAPECOMPOSITIONLAYER_H
#define SHAPECOMPOSITIONLAYER_H

#include "base_composition_layer.h"
#include <memory>
#include <vector>

namespace  eao {
class ShapeLayer;
class ShapeItemNode;

class ShapeCompositionLayer : public BaseCompositionLayer
{
public:
    ShapeCompositionLayer(const ShapeLayer &layer);

protected:
    void draw_layer(QPainter *painter, int alpha) override;

private:
    std::vector<std::unique_ptr<ShapeItemNode>> m_nodes;
};

}
#endif // SHAPECOMPOSITIONLAYER_H
