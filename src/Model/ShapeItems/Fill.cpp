#include "Fill.h"

#include <QJsonObject>

namespace eao {

const QString opacity_key = "o";
const QString color_key = "c";
const QString fill_rule_key = "r";
const QString fill_enabled_key ="fillEnabled";


Fill::Fill()
{
    m_type = ShapeType::Fill;
}

void Fill::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_fill_rule = static_cast<FillRule>(in_obj.take(fill_rule_key).toInt());
    m_opacity.decode(in_obj.take(opacity_key));
    m_color.decode(in_obj.take(color_key));
    m_fillEnabled = in_obj.take(fill_enabled_key).toBool();
}

}
