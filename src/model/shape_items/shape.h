#ifndef SHAPE_H
#define SHAPE_H

#include <model/property_system/property.h>
#include "shape_item.h"
#include "utility/primitives/bezier_path.h"

namespace eao {

class Shape : public ShapeItem
{
public:
    Shape();
    ~Shape() override;

    void decode(QJsonObject &in_obj, QList<QString>& out_messages) override;

public:
    PathDirection m_direction = PathDirection::None;
    PropertyPtr<BezierPath> m_path;
};

}
#endif // SHAPE_H
