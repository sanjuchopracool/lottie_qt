#ifndef RECTANGLENODE_H
#define RECTANGLENODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"

#include <memory>

namespace eao {
class Rectangle;

class RectangleNode : public ShapeNodeInterface, public PathNode
{
public:
    RectangleNode(const Rectangle* rectangle);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

private:
    std::unique_ptr<NodeProperty<QVector2D>> m_size;
    std::unique_ptr<NodeProperty<QVector2D>> m_center;
    std::unique_ptr<NodeProperty<QVector2D>> m_corner_radius;
    QPainterPath m_rectangle_path;
};
}

#endif // RECTANGLENODE_H
