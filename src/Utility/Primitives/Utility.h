#ifndef UTILITY_H
#define UTILITY_H

#include "BezierPath.h"
#include "Vector1D.h"

#include <QColor>
#include <QtMath>
#include <QPointF>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

namespace  eao {
class BezierPath;
struct DashElement;

template <typename T>
T remap(T value, T from_low, T from_high, T to_low, T to_high)
{
    return to_low + (value - from_low)*(to_high - to_low)/(from_high - from_low);
}
inline qreal distance_between(const QPointF &p1, const QPointF &p2)
{
    qreal x = p1.x() - p2.x();
    qreal y = p1.y() - p2.y();
    return  qSqrt( x*x + y*y);
}

inline QPointF json_to_point(const QJsonValue &val)
{
    auto array = val.toArray();
    Q_ASSERT(array.size() == 2);
    return {array.at(0).toDouble(), array.at(1).toDouble()};
}

inline void decode(QVector3D &val, const QJsonValue &in_value)
{
    auto in_array = in_value.toArray();
    Q_ASSERT(in_array.size() == 3);
    if (in_array.size() == 3)
    {
        val.setX(in_array.at(0).toDouble());
        val.setY(in_array.at(1).toDouble());
        val.setZ(in_array.at(2).toDouble());
    }
}

inline void decode(QVector2D &obj, const QJsonValue &in_value)
{
    auto in_array = in_value.toArray();
    Q_ASSERT(in_array.size() == 2);
    if (in_array.size() == 2)
    {
        obj.setX(in_array.at(0).toDouble());
        obj.setY(in_array.at(1).toDouble());
    }
}

inline void decode_keyframe_tangent(QVector2D &obj, const QJsonValue &in_value)
{
    const auto& object = in_value.toObject();
    obj.setX(object.value("x").toArray().at(0).toDouble());
    obj.setY(object.value("y").toArray().at(0).toDouble());
}

inline QColor to_color(const QVector4D &value)
{
    return QColor::fromRgbF(value.x(), value.y(), value.z(), value.w());
}

inline void decode(QVector4D &color, const QJsonValue &in_value)
{
    auto array_value = in_value.toArray();
    color.setX(array_value.at(0).toDouble());
    color.setY(array_value.at(1).toDouble());
    color.setZ(array_value.at(2).toDouble());
    color.setW(array_value.at(3).toDouble());
}

inline void decode(BezierPath &path, const QJsonValue &in_value)
{
    path.decode(in_value.isArray() ? in_value.toArray().at(0) : in_value);
}
} // namespace Lottie
#endif // UTILITY_H
