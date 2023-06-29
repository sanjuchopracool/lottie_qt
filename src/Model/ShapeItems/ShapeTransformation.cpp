#include "ShapeTransformation.h"
#include <parser/lottie/property_parser.h>

#include <QJsonObject>

namespace eao {

const QString anchor_key = "a";
const QString position_key = "p";
const QString scale_key = "s";
const QString rotation_key = "r";
const QString opacity_key = "o";
const QString skew_key = "sk";
const QString skew_axis_key = "sa";

ShapeTransformation::ShapeTransformation()
{
    m_type = ShapeType::Transform;
}

void ShapeTransformation::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    Lottie::decode(m_anchor, in_obj.take(anchor_key), out_messages);
    Lottie::decode(m_position, in_obj.take(position_key), out_messages);
    Lottie::decode(m_scale, in_obj.take(scale_key), out_messages);
    Lottie::decode(m_rotation, in_obj.take(rotation_key), out_messages);
    Lottie::decode(m_opacity, in_obj.take(opacity_key), out_messages);
    Lottie::decode(m_skew, in_obj.take(skew_key), out_messages);
    Lottie::decode(m_skew_axis, in_obj.take(skew_axis_key), out_messages);
}

}
