#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "ShapeNodeInterface.h"
#include <vector>
#include <memory>
#include <QBrush>


namespace eao {
class Group;

class GroupNode : public ShapeNodeInterface
{
public:
    GroupNode(const Group *group);
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;
private:
    const Group *m_group;
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
};

}
#endif // GROUPNODE_H
