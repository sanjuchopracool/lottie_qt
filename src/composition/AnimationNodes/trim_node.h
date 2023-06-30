#ifndef TRIMNODE_H
#define TRIMNODE_H

#include "Utility/Primitives/Utility.h"
#include "animation_node.h"
#include <Model/ShapeItems/Trim.h>
#include <Model/property_system/property.h>

#include <memory>
#include <QPainterPath>

namespace eao {
class TrimNode : public ShapeItemNode
{
public:
    TrimNode(const Trim &trim);
    bool update(FrameType t, bool force_update) override;

    qreal start() const;
    qreal end() const;
    qreal offset() const;

    auto trim_type() const { return m_trim.trim_type(); }

public:
    const Trim &m_trim;
    PropertyAnimatorPtr<Vector1D> m_start;
    PropertyAnimatorPtr<Vector1D> m_end;
    PropertyAnimatorPtr<Vector1D> m_offset;
};
}
#endif // TRIMNODE_H
