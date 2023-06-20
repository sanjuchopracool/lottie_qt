#include "Transformation.h"

#include <QJsonObject>

namespace Lottie {

const QString anchor_key = "a";
const QString position_key = "p";
const QString scale_key = "s";
const QString rotation_key = "r";
const QString opacity_key = "o";
const QString skew_key = "sk";
const QString skew_axis_key = "sa";


void Transformation::decode(const QJsonObject &in_obj)
{
    m_anchor.decode(in_obj.value(anchor_key));
    m_position.decode(in_obj.value(position_key));
    m_scale.decode(in_obj.value(scale_key));
    m_rotation.decode(in_obj.value(rotation_key));
    m_opacity.decode(in_obj.value(opacity_key));
    m_skew.decode(in_obj.value(skew_key));
    m_skew_axis.decode(in_obj.value(skew_axis_key));
}

}
