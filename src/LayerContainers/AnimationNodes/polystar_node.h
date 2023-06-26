#ifndef POLYSTARNODE_H
#define POLYSTARNODE_H

#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"

#include <memory>

namespace eao {
class PolyStar;

class PolyStarNode : public ShapeNodeInterface, public PathNode
{
public:
    PolyStarNode(const PolyStar* polystar);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

private:
    std::unique_ptr<NodeProperty<QVector2D>> m_center;
    std::unique_ptr<NodeProperty<Vector1D>> m_rotation;
    std::unique_ptr<NodeProperty<Vector1D>> m_outer_radius;
    std::unique_ptr<NodeProperty<Vector1D>> m_outer_roundness;
    std::unique_ptr<NodeProperty<Vector1D>> m_inner_radius;
    std::unique_ptr<NodeProperty<Vector1D>> m_inner_roundness;
    std::unique_ptr<NodeProperty<Vector1D>> m_num_points;

    QPainterPath m_star_path;
};
}

#endif // POLYSTARNODE_H
