#include "shape_node.h"
#include "model/shape_items/shape.h"
#include "utility/primitives/bezier_path.h"

namespace eao {

ShapeNode::ShapeNode(const Shape &shape)
    : m_shape(shape)
    , m_pathProp(shape.m_path->create_animator(this))
{
}

bool ShapeNode::update(FrameType t, bool force_update)
{
    bool result = false;
    m_pathProp->update(t);
    // TODO listen to trim paths also
    if (force_update || m_dirty) {
        m_path = m_pathProp->value().path();
        apply_trim();
        m_dirty = false;
        result = true;
    }
    return result;
}
}
