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
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_pathProp->update(t);
    //        m_shape_path = m_pathProp->value().path();
    //    }

    m_path = m_shape_path;
    return result;
}
}