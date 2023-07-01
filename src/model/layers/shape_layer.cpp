#include "shape_layer.h"
#include "model/shape_items/shape_factory.h"

#include <QJsonObject>
#include <QJsonArray>

namespace eao {

namespace {
const QString shapes_key = "shapes";
}

ShapeLayer::ShapeLayer()
{

}

ShapeLayer::~ShapeLayer()
{
}

void ShapeLayer::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    auto shapes= in_obj.take(shapes_key).toArray();
    m_shapes = ShapeFactory::shapes_from_object(shapes, out_messages);
    Layer::decode(in_obj, out_messages);
}

}
