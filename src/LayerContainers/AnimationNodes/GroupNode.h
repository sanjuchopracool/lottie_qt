#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "ShapeNodeInterface.h"
#include <vector>
#include <memory>
#include <QBrush>

#include "../CompositionLayer.h"

namespace Lottie {
class Group;

class GroupNode : public ShapeNodeInterface
{
public:
    GroupNode(const Group *group);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

    QList<PathNode*> group_paths() {
        return m_group_paths;
    }

    void render(QPainter *painter) override;
private:
    const Group *m_group;
    std::vector<std::unique_ptr<ShapeNodeInterface>> m_nodes;
    QList<PathNode*> m_group_paths;
};

}
#endif // GROUPNODE_H
