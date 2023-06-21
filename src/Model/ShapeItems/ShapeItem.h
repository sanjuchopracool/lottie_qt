#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QStringList>

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

const QList<QStringView> shape_type_names {
    u"None",
    u"Ellipse",
    u"Fill",
    u"GradientFill",
    u"Group",
    u"GradientStroke",
    u"Merge",
    u"Rectangle",
    u"Repeater",
    u"Round",
    u"Shape",
    u"Star",
    u"Stroke",
    u"Trim",
    u"Transform",
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

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages);
public:
    QString m_name;
    QString m_match_name;
    ShapeType m_type;
    bool m_hidden = false;
};
}

#endif // SHAPEITEM_H
