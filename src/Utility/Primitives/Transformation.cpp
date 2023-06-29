#include "Transformation.h"

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

void RepeaterTransformation::decode(const QJsonObject &in_obj)
{
    m_anchor.decode(in_obj.value(anchor_key));
    m_position.decode(in_obj.value(position_key));
    m_scale.decode(in_obj.value(scale_key));
    m_rotation.decode(in_obj.value(rotation_key));
    m_opacity.decode(in_obj.value(opacity_key));
    m_skew.decode(in_obj.value(skew_key));
    m_skew_axis.decode(in_obj.value(skew_axis_key));
}

void LayerTransformation::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    Lottie::decode(m_anchor, in_obj.take(anchor_key), out_messages);
    Lottie::decode(m_position, in_obj.take(position_key), out_messages);
    Lottie::decode(m_scale, in_obj.take(scale_key), out_messages);
    Lottie::decode(m_rotation, in_obj.take(rotation_key), out_messages);
    Lottie::decode(m_opacity, in_obj.take(opacity_key), out_messages);
    Lottie::decode(m_skew, in_obj.take(skew_key), out_messages);
    Lottie::decode(m_skew_axis, in_obj.take(skew_axis_key), out_messages);
}
} // namespace eao
