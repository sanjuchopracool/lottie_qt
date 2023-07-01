#include "trim_node.h"

#include <numeric>

#include <profiler.h>
#include "model/shape_items/trim.h"
namespace eao {
TrimNode::TrimNode(const Trim &trim)
    : m_trim(trim)
    , m_start(trim.m_start->create_animator(this))
    , m_end(trim.m_end->create_animator(this))
    , m_offset(trim.m_offset->create_animator(this))
{
}

bool TrimNode::update(FrameType t, bool force_update)
{
    m_dirty = false;
    m_start->update(t);
    m_end->update(t);
    m_offset->update(t);
    return m_dirty;
}

qreal TrimNode::start() const
{
    return m_start->value();
}

qreal TrimNode::end() const
{
    return m_end->value();
}

qreal TrimNode::offset() const
{
    return m_offset->value();
}
}
