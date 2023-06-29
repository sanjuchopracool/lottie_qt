#include "group_node.h"

#include "AnimationNodeFactory.h"
#include "Model/ShapeItems/Group.h"
#include "repeater_node.h"
#include <algorithm>
#include <QPainter>

namespace eao {

GroupNode::GroupNode(const Group &group)
    : m_group(group)
{
    for (const auto &shape_item : m_group.m_shapes) {
        auto node = AnimationNodeFactory::node_for_shape_item(*shape_item);
        if (node)
        {
            if (shape_item->m_type == ShapeType::Repeater) {
                RepeaterNode *rep_node = static_cast<RepeaterNode *>(node.get());
                rep_node->set_nodes(m_nodes);
            }
            m_nodes.emplace_back(std::move(node));
        }
    }

    m_is_static = std::all_of(m_nodes.cbegin(), m_nodes.cend(),
    [](const std::unique_ptr<ShapeItemNode>& node)
    {
        return node->is_static();
    });
}

bool GroupNode::update(FrameType t, bool force_update)
{
    for( auto& node : m_nodes)
    {
        node->update(t, force_update);
    }

    //    return force_update or need_update(t);

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
    return false;
}

void GroupNode::set_content(const std::vector<ShapeItemNode *> &items_before,
                            const std::vector<ShapeItemNode *> &items_after)
{
    // TODO same in shape_layer
    std::vector<ShapeItemNode *> group_items_before(items_before);
    group_items_before.reserve(items_before.size() + m_nodes.size());
    std::vector<ShapeItemNode *> group_items_after;
    group_items_after.reserve(m_nodes.size());
    std::transform(m_nodes.cbegin(),
                   m_nodes.cend(),
                   std::back_inserter(group_items_after),
                   [](const auto &it) { return it.get(); });
    auto it = m_nodes.rbegin();
    while (group_items_after.size()) {
        ShapeItemNode *item = group_items_after.back();
        group_items_after.pop_back();
        item->set_content(group_items_before, group_items_after);
        group_items_before.emplace_back(item);
    }
}
} // namespace eao
