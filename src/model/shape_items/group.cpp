#include "group.h"
#include "shape_factory.h"

#include <QJsonArray>
#include <QJsonObject>

namespace eao {

const QString it_key("it");

Group::Group()
    : ShapeItem(ShapeType::Group)
{
}

Group::~Group()
{
    qDeleteAll(m_shapes);
}

void Group::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    auto shapes= in_obj.take(it_key).toArray();
    m_shapes = ShapeFactory::shapes_from_object(shapes, out_messages);
    ShapeItem::decode(in_obj, out_messages);
}

}
