#ifndef FILL_NODE_H
#define FILL_NODE_H

#include <utility/primitives/utility.h>
#include "animation_node.h"
#include <model/property_system/property.h>
#include <composition/interfaces/painting_element.h>

#include <memory>

namespace eao {
class Fill;
class PathNode;

class FillNode : public ShapeItemNode, public PaintingElement
{
public:
    FillNode(const Fill &fill);
    bool update(FrameType t, bool force_update) override;

    void set_content(const std::vector<ShapeItemNode *> &,
                     const std::vector<ShapeItemNode *> &items_after) override;

    void draw(QPainter *painter, int parent_alpha) override;

private:
    const Fill &m_fill;
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<QVector4D> m_color;
    std::vector<const PathNode *> m_paths;
};
}

#endif // FILL_NODE_H
