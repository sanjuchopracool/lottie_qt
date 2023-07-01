#include "shape.h"

#include <parser/lottie/property_parser.h>
#include <QJsonObject>

namespace eao {

const QString path_key = "ks";
const QString direction_key = "d";

Shape::Shape()
    : ShapeItem(ShapeType::Shape)
{
}

Shape::~Shape()
{

}

void Shape::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    auto val = in_obj.take(path_key);
    Q_ASSERT(!val.isUndefined());
    Lottie::decode(m_path, val, out_messages);
    m_direction = static_cast<PathDirection>(in_obj.value(direction_key).toInt());
}
}
