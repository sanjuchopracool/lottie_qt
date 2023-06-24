#include "Shape.h"

#include <QJsonObject>

namespace eao {

const QString path_key = "ks";
const QString direction_key = "d";

Shape::Shape()
{
    m_type = ShapeType::Shape;
}

Shape::~Shape()
{

}

void Shape::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    auto val = in_obj.take(path_key);
    Q_ASSERT(!val.isUndefined());
    m_path.decode(val);
    m_direction = static_cast<PathDirection>(in_obj.value(direction_key).toInt());
}
}
