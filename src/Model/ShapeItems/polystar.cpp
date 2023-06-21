#include "polystar.h"

#include <QJsonObject>

namespace eao {

const QStringView center_key = u"p";
const QStringView rotation_key = u"r";
const QStringView outer_radius_key = u"or";
const QStringView outer_roundness_key = u"os";
const QStringView inner_radius_key = u"ir";
const QStringView inner_roundness_key = u"is";
const QStringView star_type_key = u"sy";
const QStringView direction_key = u"d";
const QStringView num_points_key = u"pt";

PolyStar::PolyStar()
{
    m_type = ShapeType::Star;
}

void PolyStar::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_center.decode(in_obj.take(center_key));
    m_rotation.decode(in_obj.take(rotation_key));
    m_outer_radius.decode(in_obj.take(outer_radius_key));
    m_outer_roundness.decode(in_obj.take(outer_roundness_key));
    m_inner_radius.decode(in_obj.take(inner_radius_key));
    m_inner_roundness.decode(in_obj.take(inner_roundness_key));
    m_num_points.decode(in_obj.take(num_points_key));
    m_star_type = static_cast<Type>(in_obj.take(star_type_key).toInt());
}

}
