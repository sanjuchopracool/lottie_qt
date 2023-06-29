#include "ShapeNode.h"

#include "Model/ShapeItems/Shape.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include "Utility/Primitives/BezierPath.h"

namespace eao {

ShapeNode::ShapeNode(const Shape *shape)
    : m_shape(shape)
{
    using PropPath = NodeProperty<BezierPath>;
    using KFVPPATH = KeyFrameValueProvider<BezierPath>;

    m_pathProp = std::make_unique<PropPath>(new KFVPPATH(shape->m_path));
    m_is_static = m_pathProp->is_static();
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
