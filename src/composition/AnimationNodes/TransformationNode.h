#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class LayerTransformation;
class LayerTransformationNode : public ShapeNodeInterface, public PropertyUpdateListener
{
public:
    LayerTransformationNode(const LayerTransformation &transformation);
    bool update(FrameType t, bool force_update) override;
    void update(FrameType t, QPainter *painter);

    void update_transform(FrameType t);
    void set_parent_transform(const LayerTransformationNode *parent_transform);

    QTransform tranform() const;
    int opacity() const { return m_opacity->value(); }

    void on_update() { m__dirty = true; }

private:
    void update_painter(QPainter *painter);

private:
    PropertyAnimatorPtr<QVector3D> m_anchor;
    PropertyAnimatorPtr<QVector3D> m_position;
    PropertyAnimatorPtr<QVector3D> m_scale;
    PropertyAnimatorPtr<Vector1D> m_rotation;
    PropertyAnimatorPtr<int> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_skew;
    PropertyAnimatorPtr<Vector1D> m_skew_axis;

    const LayerTransformationNode *m_parent_transformation = nullptr;
    bool m__dirty = true;
};

class RepeaterTransformation;
class RepeaterTransformationNode : public ShapeNodeInterface
{
public:
    RepeaterTransformationNode(const RepeaterTransformation& transformation);
    bool update(FrameType t, bool force_update) override;
    void update(FrameType t, QPainter *painter);

    void update_transform(FrameType t);
    void set_parent_transform(const LayerTransformationNode *parent_transform);

    QTransform tranform() const;
    int opacity() const { return m_opacity->value(); }

private:
    void update_painter(QPainter *painter);
private:
    std::unique_ptr<NodeProperty<QVector2D>> m_anchor;
    std::unique_ptr<NodeProperty<QVector2D>> m_position;
    std::unique_ptr<NodeProperty<QVector2D>> m_scale;
    std::unique_ptr<NodeProperty<Vector1D>> m_rotation;
    std::unique_ptr<NodeProperty<int>> m_opacity;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew;
    std::unique_ptr<NodeProperty<Vector1D>> m_skew_axis;

    const LayerTransformationNode *m_parent_transformation = nullptr;
};
}

#endif // TRANSFORMNODE_H
