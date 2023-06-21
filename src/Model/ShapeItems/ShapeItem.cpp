#include "ShapeItem.h"

#include <QJsonObject>
namespace eao {

namespace {
const QString name_key = "nm";
const QString hidden_key = "hd";
}

ShapeItem::ShapeItem()
{

}

ShapeItem::~ShapeItem()
{

}

void ShapeItem::decode(const QJsonObject &in_obj, QList<QString>&)
{
    m_name = in_obj.value(name_key).toString();
    m_hidden = in_obj.value(hidden_key).toBool();
}

}
