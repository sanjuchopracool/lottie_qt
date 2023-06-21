#ifndef LAYERFACTORY_H
#define LAYERFACTORY_H

#include <QStringList>

class QJsonObject;
namespace eao {

class QStringList;
class LayerModel;
LayerModel *layer_from_object(QJsonObject &in_value, QList<QString> &out_messages);
} // namespace eao
#endif // LAYERFACTORY_H
