#ifndef SHAPETRANSFORMNODE_H
#define SHAPETRANSFORMNODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class ShapeTransformation;
class ShapeTransformationNode : public ShapeNodeInterface, public SimpleUpdateListener
{
public:
    ShapeTransformationNode(const ShapeTransformation &transformation);
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;
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
