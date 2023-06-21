#include "LayerFactory.h"

#include "LayerModel.h"
#include "ShapeLayer.h"
#include <QJsonObject>

namespace  eao {

namespace {
const QString type_key = "ty";
}

LayerModel*  layer_from_object(const QJsonObject &in_value)
{
    LayerModel* result = nullptr;
    LayerType type = static_cast<LayerType>(in_value.value(type_key).toInt());

    switch (type) {
    case LayerType::Shape:
    {
        ShapeLayer* shape = new ShapeLayer;
        shape->decode(in_value);
        result = shape;
        break;
    }
    case LayerType::Null:
    {
        result = new LayerModel;
        result->decode(in_value);
    }
        break;
    default:
        assert(false);
        break;
    }
    assert(result != nullptr);
    return  result;
}

}
