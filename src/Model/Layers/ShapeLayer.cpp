#include "ShapeLayer.h"
#include "../ShapeItems/ShapeFactory.h"

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
    qDeleteAll(m_shapes);
}

void ShapeLayer::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    auto shapes= in_obj.take(shapes_key).toArray();
    for( auto shape : shapes)
    {
        auto shape_object = shape.toObject();
        auto shape_item = ShapeFactory::shape_from_object(shape_object, out_messages);
        if(shape_item)
            m_shapes.push_back(shape_item);
    }
    LayerModel::decode(in_obj, out_messages);
}

}
