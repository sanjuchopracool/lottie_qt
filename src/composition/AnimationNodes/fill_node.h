#ifndef FILL_NODE_H
#define FILL_NODE_H

#include "Utility/Primitives/Utility.h"
#include "animation_node.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Fill;

class FillNode : public ShapeItemNode
{
public:
    FillNode(const Fill &fill);
    bool update(FrameType t, bool force_update) override;

    void set_content(const std::vector<ShapeItemNode *> &,
                     const std::vector<ShapeItemNode *> &items_after) override;

    //    void render(QPainter *painter) override;

private:
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<QVector4D> m_color;
    std::vector<const PathNode *> m_paths;
};
}

#endif // FILL_NODE_H
