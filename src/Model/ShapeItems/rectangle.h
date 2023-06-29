#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ShapeItem.h"
#include <Model/property_system/property.h>
#include <QVector2D>

namespace eao {

class Rectangle : public ShapeItem
{
public:

    Rectangle();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    PropertyPtr<QVector2D> m_size;
    PropertyPtr<QVector2D> m_center;
    PropertyPtr<Vector1D> m_corner_radius;
    PathDirection m_direction;
};
}

#endif // RECTANGLE_H
