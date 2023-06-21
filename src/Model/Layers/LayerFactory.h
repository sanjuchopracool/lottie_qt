#ifndef LAYERFACTORY_H
#define LAYERFACTORY_H

class QJsonObject;
namespace eao {

class LayerModel;
LayerModel* layer_from_object(const QJsonObject& in_value);

}
#endif // LAYERFACTORY_H
