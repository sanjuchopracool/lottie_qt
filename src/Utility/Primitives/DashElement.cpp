#include "DashElement.h"

#include <QJsonValue>


namespace Lottie {
const QString type_key = "n";
const QString value_key = "v";


DashElement::Type from_str(const QString& str)
{
    auto result = DashElement::Type::Offset;
    if (str == "d")
        result = DashElement::Type::Dash;
    if (str == "g")
        result = DashElement::Type::Gap;

    return result;
}

DashElement::DashElement()
{
}

DashElement::~DashElement()
{

}

void DashElement::decode(const QJsonValue &in_value)
{
    QJsonObject obj = in_value.toObject();
    m_type = from_str(obj.value(type_key).toString());
    m_value.decode(obj.value(value_key));
}

}
