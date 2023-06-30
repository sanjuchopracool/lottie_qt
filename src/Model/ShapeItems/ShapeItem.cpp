#include "ShapeItem.h"

#include <QJsonObject>
namespace eao {

namespace {
const QStringView match_name_key = u"mn";
const QStringView name_key = u"nm";
const QStringView hidden_key = u"hd";
const QStringView index_key = u"ind";
}

ShapeItem::ShapeItem(ShapeType type)
    : m_type(type)
{}

ShapeItem::~ShapeItem()
{

}

void ShapeItem::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    m_name = in_obj.take(name_key).toString();
    m_match_name = in_obj.take(match_name_key).toString();
    m_hidden = in_obj.take(hidden_key).toBool();
    auto index = in_obj.take(index_key);
    if (!index.isUndefined()) {
        static bool flag = true;
        if(flag) {
            flag = false;
            out_messages.append("Warning: shape index is ignored!");
        }
    }
}
} // namespace eao
