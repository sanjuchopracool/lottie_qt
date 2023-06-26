#include "ShapeCompositionLayer.h"

#include "Model/Layers/ShapeLayer.h"
#include "AnimationNodes/TransformationNode.h"
#include "AnimationNodes/AnimationNodeFactory.h"
#include "AnimationNodes/repeater_node.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
ShapeCompositionLayer::ShapeCompositionLayer(const ShapeLayer &layer)
    : BaseCompositionLayer(layer)
{
    for (const auto &shape_item : layer.m_shapes) {
        auto node = AnimationNodeFactory::node_for_shape(shape_item);
        if (node)
        {
            if (shape_item->m_type == ShapeType::Repeater) {
                RepeaterNode *rep_node = static_cast<RepeaterNode *>(node.get());
                rep_node->set_nodes(m_nodes);
            }
            m_nodes.emplace_back(std::move(node));

        }
    }
}

void ShapeCompositionLayer::draw_layer(QPainter *painter, int alpha) {}

} // namespace eao
