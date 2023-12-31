#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include <utility/primitives/utility.h>
#include "animation_node.h"
#include <model/property_system/property.h>

#include <memory>

namespace eao {
struct LayerTransformation;
class LayerTransformationNode : public ShapeItemNode
{
public:
    LayerTransformationNode(const LayerTransformation &transformation);

    bool update(FrameType t, bool force_update) override;

    QTransform transform() const;
    int opacity() const { return m_opacity->value(); }
private:
    void update_transform(FrameType t);

private:
    PropertyAnimatorPtr<QVector3D> m_anchor;
    PropertyAnimatorPtr<QVector3D> m_position;
    PropertyAnimatorPtr<QVector3D> m_scale;
    PropertyAnimatorPtr<Vector1D> m_rotation;
    PropertyAnimatorPtr<int> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_skew;
    PropertyAnimatorPtr<Vector1D> m_skew_axis;

    const LayerTransformationNode *m_parent_transformation = nullptr;
};
}

#endif // TRANSFORMNODE_H
