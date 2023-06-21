#ifndef TRIMNODE_H
#define TRIMNODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "../../Utility/Primitives/Utility.h"

#include <memory>
#include <QPainterPath>

namespace eao {
class Trim;
class TrimNode : public ShapeNodeInterface
{
public:
    TrimNode(const Trim* trim);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;
    void setPaths(const QList<PathNode*> targets) {
        m_target_nodes = targets;
    }

public:
    std::unique_ptr<NodeProperty<Vector1D>> m_start;
    std::unique_ptr<NodeProperty<Vector1D>> m_end;
    std::unique_ptr<NodeProperty<Vector1D>> m_offset;

    const Trim *m_trim = nullptr;
    QList<PathNode*> m_target_nodes;
};
}
#endif // TRIMNODE_H
