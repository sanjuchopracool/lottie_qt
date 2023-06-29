#include "repeater.h"
#include <parser/lottie/property_parser.h>

#include <QJsonObject>

namespace eao {

const QStringView copies_key = u"c";
const QStringView offset_key = u"o";
const QStringView composite_key = u"m";
const QStringView transform_key = u"tr";

Repeater::Repeater()
{
    m_type = ShapeType::Repeater;
}

void Repeater::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    Lottie::decode(m_copies, in_obj.take(copies_key), out_messages);
    Lottie::decode(m_offset, in_obj.take(offset_key), out_messages);
    auto tr_obj = in_obj.take(transform_key).toObject();
    m_transformation.decode(tr_obj, out_messages);
    m_composite = in_obj.take(composite_key).toInt();
    if (m_composite != 1)
        out_messages.append("Error: Unsupported composite type for repeater");
}

}
