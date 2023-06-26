#ifndef FILL_H
#define FILL_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "ShapeItem.h"
#include "Utility/Primitives/Utility.h"

namespace eao {

class Fill : public ShapeItem
{
public:

    enum class FillRule {
      None,
      NonZeroWinding,
      EvenOdd
    };

    Fill();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<Vector1D> m_opacity;
    KeyFrameGroup<QVector4D> m_color;
    FillRule m_fill_rule = FillRule::None;
    bool m_fillEnabled = true;
};
}

#endif // FILL_H
