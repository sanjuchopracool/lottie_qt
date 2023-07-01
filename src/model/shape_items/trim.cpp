#include "trim.h"
#include <parser/lottie/property_parser.h>

namespace eao {

const QStringView start_key{u"s"};
const QStringView end_key{u"e"};
const QStringView offset_key{u"o"};
const QStringView trim_type_key{u"m"};
const QStringView index_key{u"ix"};

Trim::TrimType type_from_int(int i) {
    auto result = Trim::TrimType::Simultaneously;
    if (i == 2)
        result = Trim::TrimType::Individually;

    return result;
}

Trim::Trim()
    : ShapeItem(ShapeType::Trim)
{
}

void Trim::decode(QJsonObject &in_obj, QList<QString>& out_messages)
{
    Lottie::decode(m_start, in_obj.take(start_key), out_messages);
    Lottie::decode(m_end, in_obj.take(end_key), out_messages);
    Lottie::decode(m_offset, in_obj.take(offset_key), out_messages);
    m_trimType = type_from_int(in_obj.take(trim_type_key).toInt(1));
    if (m_trimType == TrimType::Individually)
        out_messages.append("Error: Individually trim not supported!");
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
