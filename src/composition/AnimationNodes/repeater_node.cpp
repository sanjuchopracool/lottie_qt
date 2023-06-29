#include "repeater_node.h"

#include "Model/ShapeItems/repeater.h"
#include <cmath>
#include <QPainter>

namespace eao {
RepeaterNode::RepeaterNode(const Repeater &repeater)
    : m_transformation(repeater.m_transformation)
    , m_copies(repeater.m_copies->create_animator(this))
    , m_offset(repeater.m_offset->create_animator(this))
{
}

bool RepeaterNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_offset->update(t);
    //        m_copies->update(t);
    //        m_transformation.update(t, force_update);
    //        for( auto& node : m_nodes)
    //        {
    //            node->update(t, force_update);
    //        }
    //    }
    //    m_path = m_star_path;
    return result;
}

void RepeaterNode::set_nodes(std::vector<std::unique_ptr<ShapeItemNode> > &nodes)
{
    m_nodes = std::move(nodes);
}

//void RepeaterNode::render(QPainter *painter)
//{
//    painter->save();
//    int offset = m_offset->value();
//    int copies = m_copies->value();
//    qDebug() << offset << " " << copies;
//    auto tr = m_transformation.tranform();
//    for (int i = 0; i < copies + offset; ++i)
//    {
//        if (i >= offset) {
//            auto nodes_count = m_nodes.size();
//            for (auto j = nodes_count - 1; j >= 0; --j) {
//                m_nodes[j]->render(painter);
//            }
//        }

//        painter->setTransform(tr, true);
//    }
//    painter->restore();
//}
}
