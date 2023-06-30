#include "Fill.h"
#include <parser/lottie/property_parser.h>

#include <QJsonObject>

namespace eao {

const QString opacity_key = "o";
const QString color_key = "c";
const QString fill_rule_key = "r";
const QString fill_enabled_key = "fillEnabled";

Fill::Fill()
    : ShapeItem(ShapeType::Fill)
{
}

void Fill::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_fill_rule = static_cast<FillRule>(in_obj.take(fill_rule_key).toInt());
    Lottie::decode(m_opacity, in_obj.take(opacity_key), out_messages);
    Lottie::decode(m_color, in_obj.take(color_key), out_messages);
    m_fillEnabled = in_obj.take(fill_enabled_key).toBool();
}

}
