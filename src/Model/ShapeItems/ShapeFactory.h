#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <QStringList>

class QJsonObject;
namespace eao {

class ShapeItem;
class ShapeFactory
{
public:
    static ShapeItem* shape_from_object(QJsonObject &in_value, QList<QString>& out_messages);
};

}

#endif // SHAPEFACTORY_H
