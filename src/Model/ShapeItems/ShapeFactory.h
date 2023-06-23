#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QStringList>

class QJsonArray;
namespace eao {

class ShapeItem;
class ShapeFactory
{
public:
    static QList<ShapeItem *> shapes_from_object(QJsonArray &in_array, QList<QString>& out_messages);
};

}

#endif // SHAPEFACTORY_H
