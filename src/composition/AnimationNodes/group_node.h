#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include "animation_node.h"
#include <vector>
#include <memory>
#include <QBrush>


namespace eao {
class Group;

class GroupNode : public ShapeItemNode
{
public:
    GroupNode(const Group &group);
    bool update(FrameType t, bool force_update) override;

    void set_content(const std::vector<ShapeItemNode *> &items_before,
                     const std::vector<ShapeItemNode *> &items_after) override;

private:
    const Group &m_group;
    std::vector<std::unique_ptr<ShapeItemNode>> m_nodes;
};

}
#endif // GROUP_NODE_H
