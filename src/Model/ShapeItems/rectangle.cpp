#include "rectangle.h"

#include <QJsonObject>

namespace eao {

const QStringView center_key = u"p";
const QStringView size_key = u"s";
const QStringView radius_key = u"r";
const QStringView direction_key = u"d";

Rectangle::Rectangle()
{
    m_type = ShapeType::Rectangle;
}

void Rectangle::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_center.decode(in_obj.take(center_key));
    m_size.decode(in_obj.take(size_key));
    m_corner_radius.decode(in_obj.take(radius_key));
    m_direction = static_cast<PathDirection>(in_obj.take(direction_key).toInt(1));
}

}
