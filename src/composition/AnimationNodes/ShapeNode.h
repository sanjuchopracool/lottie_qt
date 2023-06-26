#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "ShapeNodeInterface.h"
#include <vector>

#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "Utility/Primitives/Utility.h"
#include <memory>

namespace eao {
class Shape;

class ShapeNode : public ShapeNodeInterface, public PathNode
{
public:
    ShapeNode(const Shape* shape);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

private:
    const Shape *m_shape;
    std::unique_ptr<NodeProperty<BezierPath>> m_pathProp;
    QPainterPath m_shape_path;
};

}
#endif // SHAPENODE_H
