#include "Group.h"
#include "ShapeFactory.h"

#include <QJsonArray>
#include <QJsonObject>

namespace eao {

const QString it_key("it");

Group::Group()
{
    m_type = ShapeType::Group;
}

Group::~Group()
{
    qDeleteAll(m_shapes);
}

void Group::decode(const QJsonObject &in_obj, QList<QString>& out_messages)
{
    auto shapes= in_obj.value(it_key).toArray();
    for( auto shape : shapes)
    {
        auto shape_item = ShapeFactory::shape_from_object(shape.toObject(), out_messages);
        if(shape_item)
            m_shapes.push_back(shape_item);
    }

    ShapeItem::decode(in_obj, out_messages);
}

}
