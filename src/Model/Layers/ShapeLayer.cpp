#include "ShapeLayer.h"
#include "../ShapeItems/ShapeFactory.h"

#include <QJsonObject>
#include <QJsonArray>

namespace Lottie {

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

void ShapeLayer::decode(const QJsonObject &in_obj)
{
    auto shapes= in_obj.value(shapes_key).toArray();
    for( auto shape : shapes)
    {
        auto shape_item = ShapeFactory::shape_from_object(shape.toObject());
        if(shape_item)
            m_shapes.push_back(shape_item);
    }
    LayerModel::decode(in_obj);
}

}
