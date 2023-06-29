#ifndef RECTANGLENODE_H
#define RECTANGLENODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>
#include <memory>

namespace eao {
class Rectangle;

class RectangleNode : public ShapeNodeInterface, public PathNode, public CascadeUpdateListener
{
public:
    RectangleNode(const Rectangle &rectangle);
    bool update(FrameType t, bool force_update) override;

private:
    PropertyAnimatorPtr<QVector2D> m_size;
    PropertyAnimatorPtr<QVector2D> m_center;
    PropertyAnimatorPtr<Vector1D> m_corner_radius;
    QPainterPath m_rectangle_path;
};
}

#endif // RECTANGLENODE_H
