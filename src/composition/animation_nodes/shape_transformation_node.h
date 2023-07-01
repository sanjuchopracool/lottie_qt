#ifndef SHAPETRANSFORMNODE_H
#define SHAPETRANSFORMNODE_H

#include "animation_node.h"
#include <utility/primitives/utility.h>
#include <model/property_system/property.h>
#include <composition/interfaces/painting_element.h>

#include <memory>

namespace eao {
class ShapeTransformation;
class ShapeTransformationNode : public ShapeItemNode, public PaintingElement
{
public:
    ShapeTransformationNode(const ShapeTransformation& transformation);

    bool update(FrameType t, bool force_update) override;
    void draw(QPainter *painter, int parent_alpha) override;

    QTransform transform() const;
    int opacity() const { return m_opacity->value(); }

private:
    void update_transform(FrameType t);
private:
    PropertyAnimatorPtr<QVector2D> m_anchor;
    PropertyAnimatorPtr<QVector2D> m_position;
    PropertyAnimatorPtr<QVector2D> m_scale;
    PropertyAnimatorPtr<Vector1D> m_rotation;
    PropertyAnimatorPtr<int> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_skew;
    PropertyAnimatorPtr<Vector1D> m_skew_axis;
};

}

#endif // SHAPETRANSFORMNODE_H
