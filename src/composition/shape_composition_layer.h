#ifndef SHAPECOMPOSITIONLAYER_H
#define SHAPECOMPOSITIONLAYER_H

#include "base_composition_layer.h"
#include <composition/animation_nodes/group_node.h>
#include <memory>
#include <vector>

namespace  eao {
class ShapeLayer;
class ShapeItemNode;

class ShapeCompositionLayer : public BaseCompositionLayer, public GroupNode
{
public:
    ShapeCompositionLayer(const ShapeLayer &layer);

protected:
    void draw_layer(QPainter *painter, int alpha) override;
    void update_layer(FrameType t, bool force_update) override;

private:
    void set_content();
};

}
#endif // SHAPECOMPOSITIONLAYER_H
