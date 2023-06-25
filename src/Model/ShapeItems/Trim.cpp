#include "Trim.h"

namespace eao {
const QString start_key = "s";
const QString end_key = "e";
const QString offset_key = "o";
const QString trim_type_key = "m";
const QString index_key = "ix";

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

void Trim::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    m_start.decode(in_obj.take(start_key));
    m_end.decode(in_obj.take(end_key));
    m_offset.decode(in_obj.take(offset_key));
    m_trimType = type_from_int(in_obj.take(trim_type_key).toInt());
    auto index = in_obj.take(index_key);
    if (!index.isUndefined()) {
        static bool flag = true;
        if(flag) {
            flag = false;
            out_messages.append("Warning: property index is ignored!");
        }
    }
}
}
