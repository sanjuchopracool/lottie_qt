#ifndef REPEATER_H
#define REPEATER_H

#include <model/property_system/property.h>
#include "shape_item.h"
#include "shape_transformation.h"
#include "utility/primitives/transformation.h"

namespace eao {

class Repeater : public ShapeItem
{
public:

    Repeater();
    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    PropertyPtr<Vector1D> m_copies;
    PropertyPtr<Vector1D> m_offset;
    ShapeTransformation m_transformation;
    int m_composite = 1;
};
}

#endif // REPEATER_H
