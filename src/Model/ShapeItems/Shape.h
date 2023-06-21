#ifndef SHAPE_H
#define SHAPE_H

#include "ShapeItem.h"
#include "../Keyframes/KeyFrameGroup.h"
#include "../../Utility/Primitives/BezierPath.h"

namespace eao {

class Shape : public ShapeItem
{
public:
    Shape();
    ~Shape() override;

    void decode(const QJsonObject &in_obj) override;

public:
    PathDirection m_direction = PathDirection::None;
    KeyFrameGroup<BezierPath> m_path;
};

}
#endif // SHAPE_H
