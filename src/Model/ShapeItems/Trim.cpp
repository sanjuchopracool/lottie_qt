#include "Trim.h"

namespace eao {
const QString start_key = "s";
const QString end_key = "e";
const QString offset_key = "o";
const QString trimType_key = "m";

Trim::TrimType type_from_int(int i) {
    auto result = Trim::TrimType::Simultaneously;
    if (i == 2)
        result = Trim::TrimType::Individually;

    return result;
}

Trim::Trim()
{
    m_type = ShapeType::Trim;
}

void Trim::decode(const QJsonObject &in_obj, QList<QString>& out_messages)
{
    m_start.decode(in_obj.value(start_key));
    m_end.decode(in_obj.value(end_key));
    m_offset.decode(in_obj.value(offset_key));
    m_trimType = type_from_int(in_obj.value(trimType_key).toInt());
}
}
