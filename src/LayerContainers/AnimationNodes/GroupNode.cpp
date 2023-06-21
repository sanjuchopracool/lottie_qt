#include "GroupNode.h"

#include "../../Model/ShapeItems/Group.h"
#include "AnimationNodeFactory.h"
#include <QPainter>
#include <algorithm>

namespace eao {

GroupNode::GroupNode(const Group *group)
    : m_group(group)
{
    for (const auto& shape_item : m_group->m_shapes)
    {
        auto node = AnimationNodeFactory::node_for_shape(shape_item, m_group_paths);
        if (node)
            m_nodes.emplace_back(std::move(node));
    }

    m_is_static = std::all_of(m_nodes.cbegin(), m_nodes.cend(),
    [](const std::unique_ptr<ShapeNodeInterface>& node)
    {
        return node->is_static();
    });
}

bool GroupNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return std::any_of(m_nodes.cbegin(), m_nodes.cend(),
                [=](const std::unique_ptr<ShapeNodeInterface>& node)
    {
        return node->need_update(t);
    });
}

bool GroupNode::update(FrameType t, bool force_update)
{
    for( auto& node : m_nodes)
    {
        node->update(t, force_update);
    }

    return force_update or need_update(t);


//    bool render = force_update or need_update(t);
//    if (render)
//    {
//        painter->save();
//        painter->setTransform(QTransform());
//        QPainterPath temp_path;
//        for( auto& node : m_nodes)
//        {
//            node->update(t, painter, temp_path, force_update);
//        }

//        m_transform = painter->transform();
//        m_brush = painter->brush();
//        m_path = std::move(temp_path);
//        painter->restore();

//    }

//    path.addPath(m_path);
//    painter->setTransform(m_transform, true);
//    painter->setBrush(m_brush);
    //    return render;
}

void GroupNode::render(QPainter *painter)
{
    painter->save();
    int size = m_nodes.size();
    for( int i = size - 1; i >= 0; --i)
    {
        m_nodes[i]->render(painter);
    }
    painter->restore();
}

}
