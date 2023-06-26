#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "ShapeItem.h"

namespace eao {

class Rectangle : public ShapeItem
{
public:

    Rectangle();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<QVector2D> m_size;
    KeyFrameGroup<QVector2D> m_center;
    KeyFrameGroup<Vector1D> m_corner_radius;
    PathDirection m_direction;
};
}

#endif // RECTANGLE_H
