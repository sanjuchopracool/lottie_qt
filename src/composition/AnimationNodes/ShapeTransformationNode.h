#ifndef SHAPETRANSFORMNODE_H
#define SHAPETRANSFORMNODE_H

#include "ShapeNodeInterface.h"
#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "Utility/Primitives/Utility.h"

#include <memory>

namespace eao {
class ShapeTransformation;
class ShapeTransformationNode : public ShapeNodeInterface
{
public:
    ShapeTransformationNode(const ShapeTransformation* transform);
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

#endif // SHAPETRANSFORMNODE_H
