#ifndef TRIM_H
#define TRIM_H

#include "ShapeItem.h"
#include "../Keyframes/KeyFrameGroup.h"
#include "../../Utility/Primitives/Utility.h"

namespace eao {

class Trim : public ShapeItem
{
public:
    Trim();
    enum class TrimType
    {
        Simultaneously = 1,
        Individually = 2
    };

    virtual void decode(const QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<Vector1D> m_start;
    KeyFrameGroup<Vector1D> m_end;
    KeyFrameGroup<Vector1D> m_offset;
    TrimType m_trimType;
};
}

#endif // TRIM_H
