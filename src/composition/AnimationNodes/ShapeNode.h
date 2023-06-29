#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "ShapeNodeInterface.h"
#include <vector>

#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>
#include <memory>

namespace eao {
class Shape;

class ShapeNode : public ShapeNodeInterface, public PathNode, public CascadeUpdateListener
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
