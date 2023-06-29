#ifndef STROKENODE_H
#define STROKENODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/DashElement.h"
#include <Model/property_system/property.h>

#include <QPen>
#include <memory>

namespace eao {
class Stroke;

class StrokeNode : public ShapeNodeInterface, public SimpleUpdateListener
{
public:
    StrokeNode(const Stroke &stroke);
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;
private:
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_width;
    PropertyAnimatorPtr<QVector4D> m_color;
    std::vector<DashElement> m_dashPattern;
    QPen m_pen;
};

}

#endif // STROKENODE_H
