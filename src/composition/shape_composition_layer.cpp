#include "shape_composition_layer.h"

#include "animation_nodes/animation_node_factory.h"
#include "animation_nodes/transformation_node.h"
#include "animation_nodes/repeater_node.h"
#include "model/layers/shape_layer.h"
#include <QDebug>
#include <QPainter>

namespace  eao {
ShapeCompositionLayer::ShapeCompositionLayer(const ShapeLayer &layer)
    : BaseCompositionLayer(layer)
    , GroupNode(layer.m_shapes)
{
    set_content();
}

void ShapeCompositionLayer::draw_layer(QPainter *painter, int alpha)
{
    for (auto *item : m_paint_items) {
        item->draw(painter, alpha);
    }
}

void ShapeCompositionLayer::update_layer(FrameType t, bool force_update)
{
    BaseCompositionLayer::update_layer(t, force_update);
    for (auto it = m_nodes.rbegin(); it != m_nodes.rend(); ++it) {
        (*it)->update(t, force_update);
    }
}

void ShapeCompositionLayer::set_content()
{
    std::vector<ShapeItemNode *> group_items_before;
    std::vector<ShapeItemNode *> group_items_after;
    GroupNode::set_content(group_items_after, group_items_after);
}

} // namespace eao
