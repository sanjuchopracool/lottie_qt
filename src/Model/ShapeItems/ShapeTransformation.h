#ifndef SHAPETRANSFORMATION_H
#define SHAPETRANSFORMATION_H

#include "ShapeItem.h"
#include "../Keyframes/KeyFrameGroup.h"
#include "../../Utility/Primitives/Utility.h"

namespace eao {

class ShapeTransformation : public ShapeItem
{
public:
    ShapeTransformation();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<QVector2D> m_anchor;
    KeyFrameGroup<QVector2D> m_position;
    KeyFrameGroup<QVector2D> m_scale;
    KeyFrameGroup<Vector1D> m_rotation;
    KeyFrameGroup<Vector1D> m_opacity;
    KeyFrameGroup<Vector1D> m_skew;
    KeyFrameGroup<Vector1D> m_skew_axis;
};

}

#endif // SHAPETRANSFORMATION_H
