#include "ShapeFactory.h"

#include "ShapeItem.h"

#include "Group.h"
#include "Shape.h"
#include "Merge.h"
#include "Ellipse.h"
#include "Fill.h"
#include "Stroke.h"
#include "Trim.h"
#include "rectangle.h"
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

ShapeItem *ShapeFactory::shape_from_object(const QJsonObject &in_value, QList<QString> &out_messages)
{
    ShapeItem * result = nullptr;
    auto key = in_value.value(type_key).toString();
    auto type = from_key(key);
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
    case ShapeType::Rectangle:
        result = new Rectangle;
        break;
    case ShapeType::Stroke:
        result = new Stroke;
        break;
    case ShapeType::Trim:
        result = new Trim;
        break;
    default:
        const static QString msg("Error: Unsupproted shape item type: %1");
        auto arg = type == ShapeType::None ? key : shape_type_names[static_cast<int>(type)];
        out_messages.emplace_back(msg.arg(arg));
        break;
    }

    if (result)
    {
        result->decode(in_value, out_messages);
        result->ShapeItem::decode(in_value, out_messages);
    }

    return  result;
}

}
