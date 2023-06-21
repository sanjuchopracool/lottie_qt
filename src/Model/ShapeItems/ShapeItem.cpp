#include "ShapeItem.h"

#include <QJsonObject>
namespace eao {

namespace {
const QStringView match_name_key = u"mn";
const QStringView name_key = u"nm";
const QStringView hidden_key = u"hd";
}

ShapeItem::ShapeItem()
{

}

ShapeItem::~ShapeItem()
{

}

void ShapeItem::decode(QJsonObject &in_obj, QList<QString>&)
{
    m_name = in_obj.take(name_key).toString();
    m_match_name = in_obj.take(match_name_key).toString();
    m_hidden = in_obj.take(hidden_key).toBool();
}

}
