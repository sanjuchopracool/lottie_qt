#ifndef TRIM_H
#define TRIM_H

#include "shape_item.h"
#include <model/property_system/property.h>
#include <utility/primitives/utility.h>

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

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;
    auto trim_type() const { return m_trimType; }

public:
    PropertyPtr<Vector1D> m_start;
    PropertyPtr<Vector1D> m_end;
    PropertyPtr<Vector1D> m_offset;
    TrimType m_trimType;
};
}

#endif // TRIM_H
