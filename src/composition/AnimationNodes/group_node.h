#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include "animation_node.h"
#include <composition/interfaces/painting_element.h>
#include <memory>
#include <vector>
#include <QBrush>

namespace eao {
class Group;
class ShapeItem;

class GroupNode : public ShapeItemNode, public PaintingElement
{
public:
    GroupNode(const std::vector<ShapeItem *> &shapes);
    bool update(FrameType t, bool force_update) override;

    void set_content(const std::vector<ShapeItemNode *> &items_before,
                     const std::vector<ShapeItemNode *> &items_after) override;

protected:
    void draw(QPainter *painter, int alpha) override;
    std::vector<std::unique_ptr<ShapeItemNode>> m_nodes;
    std::vector<PaintingElement *> m_paint_items;
};

} // namespace eao
#endif // GROUP_NODE_H
