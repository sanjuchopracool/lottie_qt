#ifndef SHAPETRANSFORMNODE_H
#define SHAPETRANSFORMNODE_H

#include "animation_node.h"
#include <utility/primitives/utility.h>
#include <model/property_system/property.h>

#include <memory>

namespace eao {
class ShapeTransformation;
class ShapeTransformationNode : public ShapeItemNode
{
public:
    ShapeTransformationNode(const ShapeTransformation &transformation);
    bool update(FrameType t, bool force_update) override;

private:
    PropertyAnimatorPtr<QVector2D> m_anchor;
    PropertyAnimatorPtr<QVector2D> m_position;
    PropertyAnimatorPtr<QVector2D> m_scale;
    PropertyAnimatorPtr<Vector1D> m_rotation;
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_skew;
    PropertyAnimatorPtr<Vector1D> m_skew_axis;
};
}

#endif // SHAPETRANSFORMNODE_H
