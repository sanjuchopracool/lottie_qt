#ifndef REPEATERNODE_H
#define REPEATERNODE_H

#include "TransformationNode.h"
#include "animation_node.h"
#include "path_node.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Repeater;

class RepeaterNode : public ShapeItemNode, public PathNode
{
public:
    RepeaterNode(const Repeater &repeater);
    bool update(FrameType t, bool force_update) override;

    void set_nodes(std::vector<std::unique_ptr<ShapeItemNode>> &nodes);

private:
    PropertyAnimatorPtr<QVector2D> m_center;
    PropertyAnimatorPtr<Vector1D> m_copies;
    PropertyAnimatorPtr<Vector1D> m_offset;
    RepeaterTransformationNode m_transformation;

    QPainterPath m_star_path;
    std::vector<std::unique_ptr<ShapeItemNode>> m_nodes;
};
}

#endif // REPEATERNODE_H
