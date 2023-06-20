#include "Fill.h"

#include <QJsonObject>

namespace Lottie {

const QString opacity_key = "o";
const QString color_key = "c";
const QString fill_rule_key = "r";

Fill::Fill()
{
    m_type = ShapeType::Fill;
}

void Fill::decode(const QJsonObject &in_obj)
{
    m_fill_rule = static_cast<FillRule>(in_obj.value(fill_rule_key).toInt());
    m_opacity.decode(in_obj.value(opacity_key));
    m_color.decode(in_obj.value(color_key));
}

}
