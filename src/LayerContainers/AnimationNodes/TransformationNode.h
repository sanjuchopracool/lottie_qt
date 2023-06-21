#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "../../Utility/Primitives/Utility.h"

#include <memory>

namespace eao {
class Transformation;
class TransformationNode : public ShapeNodeInterface
{
public:
    TransformationNode(const Transformation& transformation);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;
    void update(FrameType t, QPainter *painter);

    void update_transform(FrameType t);
    void set_parent_transform(const TransformationNode* parent_transform);

    QTransform tranform() const;
private:
    void update_painter(QPainter *painter);
private:
    std::unique_ptr<NodeProperty<QVector3D>> m_anchor;
    std::unique_ptr<NodeProperty<QVector3D>> m_position;
    std::unique_ptr<NodeProperty<QVector3D>> m_scale;
    std::unique_ptr<NodeProperty<Vector1D>> m_rotation;
    std::unique_ptr<NodeProperty<Vector1D>> m_opacity;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew_axis;

    const TransformationNode* m_parent_transformation = nullptr;
};
}

#endif // TRANSFORMNODE_H
