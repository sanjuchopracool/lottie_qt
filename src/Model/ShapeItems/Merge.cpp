#include "Merge.h"

#include <QJsonObject>

namespace eao {

const QString mode_key("mm");
const QString match_name_key("mn");

Merge::Merge()
{
    m_type = ShapeType::Merge;
}

void Merge::decode(const QJsonObject &in_obj)
{
    m_mode = static_cast<MergeMode>(in_obj.value(mode_key).toInt());
    m_match_name = in_obj.value(match_name_key).toString();
}

}
