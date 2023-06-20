#ifndef DASHELEMENT_H
#define DASHELEMENT_H

#include <vector>
#include "Vector1D.h"

#include "../../Model/Keyframes/KeyFrameGroup.h"

class QJsonValue;

namespace Lottie {
struct DashElementData;

struct DashElement
{
    DashElement();
    ~DashElement();
    enum Type
    {
        Offset,
        Dash,
        Gap
    };

    Type m_type;
    KeyFrameGroup<Vector1D> m_value;

    void decode(const QJsonValue& in_value);
};

static void decode(std::vector<DashElement>& elements, const QJsonValue& in_value) {
    QJsonArray array = in_value.toArray();
    elements.resize(array.size());
    for(int i = 0; i < array.size(); ++i)
        elements[i].decode(array.at(i));
}
}

#endif // DASHELEMENT_H
