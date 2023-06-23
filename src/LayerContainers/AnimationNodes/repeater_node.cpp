#include "repeater_node.h"

#include "../../Model/ShapeItems/repeater.h"
#include "../../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include <cmath>
#include <QPainter>

namespace eao {
RepeaterNode::RepeaterNode(const Repeater *repeater)
    : m_transformation(repeater->m_transformation)
{
    using Prop1D = NodeProperty<Vector1D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_copies = std::make_unique<Prop1D>(new KFVP1D(repeater->m_copies));
    m_offset = std::make_unique<Prop1D>(new KFVP1D(repeater->m_offset));
    m_is_static = m_copies->is_static() && m_offset->is_static() &&
                  m_transformation.is_static();

}

bool RepeaterNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    bool needUpdate =  m_copies->needs_update(t) || m_offset->needs_update(t) ||
                      m_transformation.need_update(t);
    return needUpdate || std::any_of(m_nodes.cbegin(), m_nodes.cend(),
                                     [=](const std::unique_ptr<ShapeNodeInterface>& node)
                                     {
                                         return node->need_update(t);
                                     });
}

bool RepeaterNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_offset->update(t);
        m_copies->update(t);
        m_transformation.update(t, force_update);
        for( auto& node : m_nodes)
        {
            node->update(t, force_update);
        }
    }
//    m_path = m_star_path;
    return result;
}

void RepeaterNode::set_nodes(std::vector<std::unique_ptr<ShapeNodeInterface> > &nodes)
{
    m_nodes = std::move(nodes);
}

void RepeaterNode::render(QPainter *painter)
{
    painter->save();
    int size = m_nodes.size();
//    int offset = m_offset->value();
    int copies = m_copies->value();
//    qDebug() << offset << " " << copies;
    qDebug() << copies;
    auto tr = m_transformation.tranform();
    qDebug() << tr;
    for (int i = 0; i < copies; ++i)
    {
        for( int i = size - 1; i >= 0; --i)
        {
//            if (i < offset)
//                continue;
            m_nodes[i]->render(painter);
        }
        painter->setTransform(tr, true);
    }
    painter->restore();
}
}
