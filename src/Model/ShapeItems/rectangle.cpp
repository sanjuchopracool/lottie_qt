#include "rectangle.h"

#include <QJsonObject>

namespace eao {

const QStringView center_key = u"p";
const QStringView size_key = u"s";
const QStringView radius_key = u"r";

Rectangle::Rectangle()
{
    m_type = ShapeType::Rectangle;
}

void Rectangle::decode(const QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_center.decode(in_obj.value(center_key));
    m_size.decode(in_obj.value(size_key));
    m_corner_radius.decode(in_obj.value(radius_key));
}

}
