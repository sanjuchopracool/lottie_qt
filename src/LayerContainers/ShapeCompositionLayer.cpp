#include "ShapeCompositionLayer.h"

#include "../Model/Layers/ShapeLayer.h"
#include "AnimationNodes/TransformationNode.h"
#include "AnimationNodes/AnimationNodeFactory.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
ShapeCompositionLayer::ShapeCompositionLayer(const ShapeLayer *layer, const PaintBufferInfo &info)
    : TransformedPaintBuffer(layer->m_transform, info, layer)
{
    QList<PathNode*> paths;
    for (const auto& shape_item : layer->m_shapes)
    {
        auto node = AnimationNodeFactory::node_for_shape(shape_item, paths);
        if (node)
        {
            m_nodes.emplace_back(std::move(node));

        }
    }

    ShapeCompositionLayer::update_buffer_info(info);

    m_is_static = m_is_static and std::all_of(m_nodes.cbegin(), m_nodes.cend(),
    [](const std::unique_ptr<ShapeNodeInterface>& node)
    {
        return node->is_static();
    });
}

bool ShapeCompositionLayer::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    if (m_transformation->need_update(t))
        return true;

    return std::any_of(m_nodes.cbegin(), m_nodes.cend(),
                [=](const std::unique_ptr<ShapeNodeInterface>& node)
    {
        return node->need_update(t);
    });
}

bool ShapeCompositionLayer::update(FrameType t, bool force_update)
{
    if ((not force_update) and (not m_layer_model->in_range(t)))
        return false;

    bool render = force_update or need_update(t);
    if (render)
    {
        int size = m_nodes.size();
        for( int i = 0; i < size; ++i)
        {
            m_nodes[i]->update(t, force_update);
        }

        // render in reverse order
        auto painter = TransformedPaintBuffer::painter(t);
        for( int i = size - 1; i >= 0; --i)
        {
            m_nodes[i]->render(painter.get());
        }
    }

    return render;
}

}
