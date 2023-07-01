#ifndef RECTANGLENODE_H
#define RECTANGLENODE_H

#include <utility/primitives/utility.h>
#include "animation_node.h"
#include "shape_path_node.h"
#include <model/property_system/property.h>

namespace eao {

class Rectangle;

class RectangleNode : public ShapePathNode
{
public:
    RectangleNode(const Rectangle &rectangle);
    bool update(FrameType t, bool force_update) override;

private:
    void create_path();

private:
    const eao::Rectangle &m_rectangle;
    PropertyAnimatorPtr<QVector2D> m_size;
    PropertyAnimatorPtr<QVector2D> m_center;
    PropertyAnimatorPtr<Vector1D> m_corner_radius;
};

} // namespace eao

#endif // RECTANGLENODE_H
