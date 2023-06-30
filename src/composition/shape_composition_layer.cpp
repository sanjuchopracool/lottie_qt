#include "shape_composition_layer.h"

#include "Model/Layers/ShapeLayer.h"
#include "AnimationNodes/TransformationNode.h"
#include "AnimationNodes/AnimationNodeFactory.h"
#include "AnimationNodes/repeater_node.h"
#include <QPainter>
#include <QDebug>

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
    for (auto it = m_nodes.cbegin(); it != m_nodes.cend(); ++it) {
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
