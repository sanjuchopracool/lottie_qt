#ifndef REPEATER_H
#define REPEATER_H

#include "ShapeItem.h"
#include "../Keyframes/KeyFrameGroup.h"
#include "../../Utility/Primitives/Transformation.h"
#include "ShapeTransformation.h"

namespace eao {

class Repeater : public ShapeItem
{
public:

    Repeater();
    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<Vector1D> m_copies;
    KeyFrameGroup<Vector1D> m_offset;
    RepeaterTransformation m_transformation;
    int m_composite = 1;
};
}

#endif // REPEATER_H
