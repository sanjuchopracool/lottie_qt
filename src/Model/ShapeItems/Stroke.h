#ifndef STROKE_H
#define STROKE_H

#include "ShapeItem.h"
#include "Utility/Primitives/DashElement.h"
#include <Model/property_system/property.h>
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
    PropertyPtr<Vector1D> m_opacity;
    PropertyPtr<Vector1D> m_width;
    PropertyPtr<QVector4D> m_color;
    //    PropertyPtr<std::vector<DashElement>> m_dashPattern;
    bool m_fillEnabled = false;
    QPen m_pen;
};
}

#endif // STROKE_H
