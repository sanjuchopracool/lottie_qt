#include "Ellipse.h"

#include <parser/lottie/property_parser.h>
#include <QJsonObject>

namespace eao {

const QString direction_key = "d";
const QString position_key = "p";
const QString size_key = "s";

Ellipse::Ellipse()
    : ShapeItem(ShapeType::Ellipse)
{
}

void Ellipse::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    Lottie::decode(m_size, in_obj.take(size_key), out_messages);
    Lottie::decode(m_position, in_obj.take(position_key), out_messages);
    m_direction = static_cast<PathDirection>(in_obj.take(direction_key).toInt(1));
}

}
