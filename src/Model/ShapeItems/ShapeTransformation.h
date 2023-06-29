#ifndef SHAPETRANSFORMATION_H
#define SHAPETRANSFORMATION_H

#include <Model/property_system/property.h>
#include "ShapeItem.h"
#include "Utility/Primitives/Utility.h"

namespace eao {

class ShapeTransformation : public ShapeItem
{
public:
    ShapeTransformation();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    PropertyPtr<QVector2D> m_anchor;
    PropertyPtr<QVector2D> m_position;
    PropertyPtr<QVector2D> m_scale;
    PropertyPtr<Vector1D> m_rotation;
    PropertyPtr<Vector1D> m_opacity;
    PropertyPtr<Vector1D> m_skew;
    PropertyPtr<Vector1D> m_skew_axis;
};

}

#endif // SHAPETRANSFORMATION_H
