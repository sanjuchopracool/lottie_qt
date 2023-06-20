#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "../../Utility/Primitives/Utility.h"

#include <memory>

namespace Lottie {
class ShapeTransformation;
class ShapeTransformationNode : public ShapeNodeInterface
{
public:
    ShapeTransformationNode(const ShapeTransformation* transform);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;
private:
    const ShapeTransformation* m_transform;

    std::unique_ptr<NodeProperty<QVector2D>> m_anchor;
    std::unique_ptr<NodeProperty<QVector2D>> m_position;
    std::unique_ptr<NodeProperty<QVector2D>> m_scale;
    std::unique_ptr<NodeProperty<Vector1D>> m_rotation;
    std::unique_ptr<NodeProperty<Vector1D>> m_opacity;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew_axis;
};
}

#endif // TRANSFORMNODE_H
