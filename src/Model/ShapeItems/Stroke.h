#ifndef STROKE_H
#define STROKE_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "ShapeItem.h"
#include "Utility/Primitives/DashElement.h"
#include <QPen>

namespace eao {

class Stroke : public ShapeItem
{
public:

    enum class StrokeRule {
      None,
      NonZeroWinding,
      EvenOdd
    };

    Stroke();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<Vector1D> m_opacity;
    KeyFrameGroup<Vector1D> m_width;
    KeyFrameGroup<QVector4D> m_color;
    KeyFrameGroup<std::vector<DashElement>> m_dashPattern;
    bool m_fillEnabled = false;
    QPen m_pen;
};
}

#endif // STROKE_H
