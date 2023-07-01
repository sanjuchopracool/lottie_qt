#include "group_node.h"

#include "animation_node_factory.h"
#include "model/shape_items/group.h"
#include "repeater_node.h"
#include <algorithm>
#include <QPainter>

namespace eao {

GroupNode::GroupNode(const std::vector<ShapeItem *> &shapes)
{
    for (const auto &shape_item : shapes) {
        auto node = AnimationNodeFactory::node_for_shape_item(*shape_item);
        if (node)
        {
            node->add_listener(this);
            if (shape_item->type() == ShapeType::Repeater) {
                RepeaterNode *rep_node = static_cast<RepeaterNode *>(node.get());
                rep_node->set_nodes(m_nodes);
            }
            m_nodes.emplace_back(std::move(node));
        }
    }
}

bool GroupNode::update(FrameType t, bool force_update)
{
    m_dirty = false;
    for (auto it = m_nodes.rbegin(); it != m_nodes.rend(); ++it) {
        (*it)->update(t, force_update);
    }
    return m_dirty;
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
    while (group_items_after.size()) {
        ShapeItemNode *item = group_items_after.back();
        group_items_after.pop_back();
        item->set_content(group_items_before, group_items_after);
        group_items_before.emplace_back(item);

        auto *paint_element = dynamic_cast<PaintingElement *>(item);
        if (paint_element)
            m_paint_items.emplace_back(paint_element);
    }
}

void GroupNode::draw(QPainter *painter, int alpha)
{
    painter->save();
    for (auto *item : m_paint_items) {
        item->draw(painter, alpha);
    }
    painter->restore();
}
} // namespace eao
