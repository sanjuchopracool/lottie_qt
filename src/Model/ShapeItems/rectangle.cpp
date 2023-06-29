#include "rectangle.h"
#include <parser/lottie/property_parser.h>

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
    Lottie::decode(m_center, in_obj.take(center_key), out_messages);
    Lottie::decode(m_size, in_obj.take(size_key), out_messages);
    Lottie::decode(m_corner_radius, in_obj.take(radius_key), out_messages);
    m_direction = static_cast<PathDirection>(in_obj.take(direction_key).toInt(1));
}

}
