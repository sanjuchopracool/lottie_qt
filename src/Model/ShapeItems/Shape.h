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

    void decode(QJsonObject &in_obj, QList<QString>& out_messages) override;

public:
    PathDirection m_direction = PathDirection::None;
    KeyFrameGroup<BezierPath> m_path;
};

}
#endif // SHAPE_H
