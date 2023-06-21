#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QString>

class QJsonObject;
class QPainterPath;

namespace eao {

enum class ShapeType {
    None,
    Ellipse,
    Fill,
    GradientFill,
    Group,
    GradientStroke,
    Merge,
    Rectangle,
    Repeater,
    Round,
    Shape,
    Star,
    Stroke,
    Trim,
    Transform,
};

enum class PathDirection
{
    None = 0,
    Clockwise = 1,
    UserSetClockwise,
    CounterClockwise
};

class ShapeItem
{
public:
    ShapeItem();
    virtual ~ShapeItem();

    virtual void decode(const QJsonObject& in_obj);
public:
    QString m_name;
    ShapeType m_type;
    bool m_hidden = false;
};
}

#endif // SHAPEITEM_H
