#ifndef REPEATERNODE_H
#define REPEATERNODE_H

#include "ShapeNodeInterface.h"
#include "TransformationNode.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Repeater;

class RepeaterNode : public ShapeNodeInterface, public PathNode, public CascadeUpdateListener
{
public:
    RepeaterNode(const Repeater &repeater);
    bool update(FrameType t, bool force_update) override;

    void set_nodes(std::vector<std::unique_ptr<ShapeNodeInterface>>& nodes);
    void render(QPainter *painter) override;
private:
    PropertyAnimatorPtr<QVector2D> m_center;
    PropertyAnimatorPtr<Vector1D> m_copies;
    PropertyAnimatorPtr<Vector1D> m_offset;
    RepeaterTransformationNode m_transformation;

    QPainterPath m_star_path;
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
};
}

#endif // REPEATERNODE_H
