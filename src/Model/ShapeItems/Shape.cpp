#include "Shape.h"

#include <QJsonObject>

namespace Lottie {

const QString path_key = "ks";
const QString direction_key = "d";

Shape::Shape()
{
    m_type = ShapeType::Shape;
}

Shape::~Shape()
{

}

void Shape::decode(const QJsonObject &in_obj)
{
    m_path.decode(in_obj.value(path_key));
    m_direction = static_cast<PathDirection>(in_obj.value(direction_key).toInt());
}
}
