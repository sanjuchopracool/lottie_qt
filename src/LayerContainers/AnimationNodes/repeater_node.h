#ifndef REPEATERNODE_H
#define REPEATERNODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "../../Utility/Primitives/Vector1D.h"
#include "TransformationNode.h"


#include <memory>

namespace eao {
class Repeater;

class RepeaterNode : public ShapeNodeInterface, public PathNode
{
public:
    RepeaterNode(const Repeater* repeater);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

    void set_nodes(std::vector<std::unique_ptr<ShapeNodeInterface>>& nodes);
    void render(QPainter *painter) override;
private:
    std::unique_ptr<NodeProperty<QVector2D>> m_center;
    std::unique_ptr<NodeProperty<Vector1D>> m_copies;
    std::unique_ptr<NodeProperty<Vector1D>> m_offset;
    RepeaterTransformationNode m_transformation;

    QPainterPath m_star_path;
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
};
}

#endif // REPEATERNODE_H
