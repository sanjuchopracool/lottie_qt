#include "Stroke.h"

#include <QJsonObject>

namespace eao {

const QString opacity_key ="o";
const QString color_key ="c";
const QString width_key ="w";
const QString lineCap_key ="lc";
const QString lineJoin_key ="lj";
const QString miterLimit_key ="ml";
const QString dashPattern_key ="d";
const QString fill_enabled_key ="fillEnabled";

Qt::PenCapStyle int_to_cap_style(int i) {
    auto result = Qt::RoundCap;
    switch (i) {
    case 1:
        result = Qt::FlatCap;
        break;
    case 3:
        result = Qt::SquareCap;
        break;
    default:
        break;
    }
    return result;
}

Qt::PenJoinStyle int_to_join_style(int i) {
    auto result = Qt::RoundJoin;
    switch (i) {
    case 1:
        result = Qt::MiterJoin;
        break;
    case 3:
        result = Qt::BevelJoin;
        break;
    default:
        break;
    }
    return result;
}

Stroke::Stroke()
{
    m_type = ShapeType::Stroke;
}

void Stroke::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    m_pen.setCapStyle(int_to_cap_style(in_obj.take(lineCap_key).toInt()));
    m_pen.setJoinStyle(int_to_join_style(in_obj.take(lineJoin_key).toInt()));
    m_pen.setMiterLimit(in_obj.take(miterLimit_key).toDouble(4));
    m_opacity.decode(in_obj.take(opacity_key));
    m_width.decode(in_obj.take(width_key));
    m_color.decode(in_obj.take(color_key));
    if (in_obj.contains(dashPattern_key))
        m_dashPattern.decode(in_obj.take(dashPattern_key));
    m_fillEnabled = in_obj.take(fill_enabled_key).toBool();
}

}
