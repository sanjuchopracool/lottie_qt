#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

class QJsonObject;
namespace Lottie {

class ShapeItem;
class ShapeFactory
{
public:
    static ShapeItem* shape_from_object(const QJsonObject &in_value);
};

}

#endif // SHAPEFACTORY_H
