#include "LayerFactory.h"

#include "LayerModel.h"
#include "ShapeLayer.h"
#include "solid_layer.h"
#include <QJsonObject>
#include <QStringList>

namespace  eao {

namespace {
const QString type_key = "ty";
}

LayerModel *layer_from_object(const QJsonObject &in_value , QList<QString> &out_messages)
{
    LayerModel* result = nullptr;
    int t = in_value.value(type_key).toInt();
    LayerType type = static_cast<LayerType>(t);

    switch (type) {
    case LayerType::Shape:
    {
        ShapeLayer* shape = new ShapeLayer;
        shape->decode(in_value, out_messages);
        result = shape;
        break;
    }
    case LayerType::Null:
    {
        result = new LayerModel;
        result->decode(in_value, out_messages);
    }
        break;
    case LayerType::Solid:
    {
        result = new SolidLayer;
        result->decode(in_value, out_messages);
    }
    break;
    default:
        const static QString msg("Error: Unsupproted layer type: %1");
        out_messages.emplace_back(msg.arg(layer_type_names[t]));
        break;
    }
    return  result;
}

}
