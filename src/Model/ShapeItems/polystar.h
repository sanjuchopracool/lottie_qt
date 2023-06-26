#ifndef POLYSTAR_H
#define POLYSTAR_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "ShapeItem.h"

namespace eao {

class PolyStar : public ShapeItem
{
public:

    PolyStar();

    enum class Type {
        Star,
        PolyStar,
    };

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<QVector2D> m_center;
    KeyFrameGroup<Vector1D> m_rotation;
    KeyFrameGroup<Vector1D> m_outer_radius;
    KeyFrameGroup<Vector1D> m_outer_roundness;
    KeyFrameGroup<Vector1D> m_inner_radius;
    KeyFrameGroup<Vector1D> m_inner_roundness;
    KeyFrameGroup<Vector1D> m_num_points;

    Type m_star_type;
};
}

#endif // POLYSTAR_H
