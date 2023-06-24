#include "Ellipse.h"

#include <QJsonObject>

namespace eao {

const QString direction_key = "d";
const QString position_key = "p";
const QString size_key = "s";

Ellipse::Ellipse()
{
    m_type = ShapeType::Ellipse;
}

void Ellipse::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_size.decode(in_obj.take(size_key));
    m_position.decode(in_obj.take(position_key));
    m_direction = static_cast<PathDirection>(in_obj.take(direction_key).toInt(1));
}

}
