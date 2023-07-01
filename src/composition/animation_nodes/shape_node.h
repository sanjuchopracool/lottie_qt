#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "animation_node.h"
#include "shape_path_node.h"
#include <vector>

#include <utility/primitives/utility.h>
#include <model/property_system/property.h>
#include <memory>

namespace eao {
class Shape;

class ShapeNode : public ShapePathNode
{
public:
    ShapeNode(const Shape &shape);
    bool update(FrameType t, bool force_update) override;

private:
    const Shape &m_shape;
    PropertyAnimatorPtr<BezierPath> m_pathProp;
    QPainterPath m_shape_path;
};

}
#endif // SHAPENODE_H
