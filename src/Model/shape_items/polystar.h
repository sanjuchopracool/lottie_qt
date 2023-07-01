#ifndef POLYSTAR_H
#define POLYSTAR_H

#include "shape_item.h"
#include <model/property_system/property.h>
#include <QVector2D>

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
    PropertyPtr<QVector2D> m_center;
    PropertyPtr<Vector1D> m_rotation;
    PropertyPtr<Vector1D> m_outer_radius;
    PropertyPtr<Vector1D> m_outer_roundness;
    PropertyPtr<Vector1D> m_inner_radius;
    PropertyPtr<Vector1D> m_inner_roundness;
    PropertyPtr<Vector1D> m_num_points;

    Type m_star_type;
};
}

#endif // POLYSTAR_H
