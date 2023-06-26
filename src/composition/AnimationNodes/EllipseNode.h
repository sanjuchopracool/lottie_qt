#ifndef ELLIPSENODE_H
#define ELLIPSENODE_H

#include "ShapeNodeInterface.h"
#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "Utility/Primitives/Utility.h"

#include <memory>

namespace eao {
class Ellipse;

class EllipseNode : public ShapeNodeInterface, public PathNode
{
public:
    EllipseNode(const Ellipse* ellipse);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

private:
    std::unique_ptr<NodeProperty<QVector2D>> m_size;
    std::unique_ptr<NodeProperty<QVector2D>> m_position;
    QPainterPath m_ellipse_path;
};
}

#endif // ELLIPSENODE_H
