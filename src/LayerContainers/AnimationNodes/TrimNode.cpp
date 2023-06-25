#include "TrimNode.h"

#include <numeric>

#include "../../AutoProfiler.h"
#include "../../Model/ShapeItems/Trim.h"
#include "../../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
namespace eao {
TrimNode::TrimNode(const Trim *trim)
    : m_trim(trim)
{
    using Prop1D = NodeProperty<Vector1D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_start = std::make_unique<Prop1D>(new KFVP1D(trim->m_start));
    m_end = std::make_unique<Prop1D>(new KFVP1D(trim->m_end));
    m_offset = std::make_unique<Prop1D>(new KFVP1D(trim->m_offset));

    m_is_static = m_start->is_static() and m_end->is_static() and m_offset->is_static();
}

bool TrimNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_start->needs_update(t) or m_end->needs_update(t) or m_offset->needs_update(t);
}

bool TrimNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_start->update(t);
        m_end->update(t);
        m_offset->update(t);
    }

    double start = m_start->value()/100;
    double end = m_end->value()/100;
//    double offset = m_offset->value();
    if (std::abs(end-start) > std::numeric_limits<double>::epsilon() )
    {
        if (std::abs(end - start - 1) > std::numeric_limits<double>::epsilon())
        {
            qreal gap = (end - start) / 100.0;
            for (auto path_node : m_target_nodes) {
                //            AutoProfiler p("T");
                const QPainterPath &path = path_node->path();
                QPainterPath new_path;
                new_path.moveTo(path.pointAtPercent(start));
                for (qreal trim = start + gap; trim <= end; trim += gap) {
                    new_path.lineTo(path.pointAtPercent(trim));
                }
                path_node->set_path(new_path);
                //                qDebug() << start << end << path.length() << new_path.length();
            }
        }

    }
    else
    {
        for (auto path_node : m_target_nodes) {
            path_node->set_path(QPainterPath());
        }
    }

    return result;
}
}
