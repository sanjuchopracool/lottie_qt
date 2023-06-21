#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "ShapeItem.h"
#include "../Keyframes/KeyFrameGroup.h"
#include "../../Utility/Primitives/Utility.h"

namespace eao {

class Ellipse : public ShapeItem
{
public:

    enum class Direction {
      Clockwise,
      UserSetClockwise,
      CounterClockwise
    };

    Ellipse();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<QVector2D> m_size;
    KeyFrameGroup<QVector2D> m_position;
    Direction m_direction = Direction::Clockwise;
};
}

#endif // ELLIPSE_H
