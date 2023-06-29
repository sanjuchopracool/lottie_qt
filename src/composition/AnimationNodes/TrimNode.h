#ifndef TRIMNODE_H
#define TRIMNODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>

#include <memory>
#include <QPainterPath>

namespace eao {
class Trim;
class TrimNode : public ShapeNodeInterface, public CascadeUpdateListener
{
public:
    TrimNode(const Trim &trim);
    bool update(FrameType t, bool force_update) override;
    void set_paths(const QList<PathNode *> targets) { m_target_nodes = targets; }

public:
    PropertyAnimatorPtr<Vector1D> m_start;
    PropertyAnimatorPtr<Vector1D> m_end;
    PropertyAnimatorPtr<Vector1D> m_offset;

    const Trim &m_trim;
    QList<PathNode*> m_target_nodes;
};
}
#endif // TRIMNODE_H
