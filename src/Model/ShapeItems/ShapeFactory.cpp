#include "ShapeFactory.h"

#include "ShapeItem.h"

#include "Group.h"
#include "Shape.h"
#include "Merge.h"
#include "Ellipse.h"
#include "Fill.h"
#include "Stroke.h"
#include "Trim.h"
#include "ShapeTransformation.h"

#include <QMap>
#include <QJsonObject>

namespace eao {

const QString type_key = "ty";
const QMap<QString, ShapeType> keyToType
{
    {"el", ShapeType::Ellipse},
    {"fl", ShapeType::Fill},
    {"gf", ShapeType::GradientFill},
    {"gr", ShapeType::Group},
    {"gs", ShapeType::GradientStroke},
    {"mm", ShapeType::Merge},
    {"rc", ShapeType::Rectangle},
    {"rp", ShapeType::Repeater},
    {"rd", ShapeType::Round},
    {"sh", ShapeType::Shape},
    {"sr", ShapeType::Star},
    {"st", ShapeType::Stroke},
    {"tm", ShapeType::Trim},
    {"tr", ShapeType::Transform},
};

ShapeType from_key(const QString& key)
{
    auto found = keyToType.find(key);
    if( found != keyToType.end())
        return  found.value();

    return  ShapeType::None;
}

ShapeItem *ShapeFactory::shape_from_object(const QJsonObject &in_value)
{
    ShapeItem * result = nullptr;
    auto type = from_key(in_value.value(type_key).toString());
    switch (type) {
    case ShapeType::Group:
        result = new Group;
        break;
    case ShapeType::Shape:
        result = new Shape;
        break;
    case ShapeType::Merge:
        result = new Merge;
        break;
    case ShapeType::Fill:
        result = new Fill;
        break;
    case ShapeType::Transform:
        result = new ShapeTransformation;
        break;
    case ShapeType::Ellipse:
        result = new Ellipse;
        break;
    case ShapeType::Stroke:
        result = new Stroke;
        break;
    case ShapeType::Trim:
        result = new Trim;
        break;
    default:
        break;
    }

    assert(result != nullptr);
    if (result)
    {
        result->decode(in_value);
        result->ShapeItem::decode(in_value);
    }

    return  result;
}

}
