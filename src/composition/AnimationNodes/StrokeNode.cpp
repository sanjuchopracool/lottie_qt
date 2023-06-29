#include "StrokeNode.h"

#include "Model/ShapeItems/Stroke.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include <QPainter>

namespace eao {
StrokeNode::StrokeNode(const Stroke &stroke)
    : m_color(stroke.m_color->create_animator(this))
    , m_opacity(stroke.m_opacity->create_animator(this))
    , m_width(stroke.m_width->create_animator(this))
{
    m_pen = stroke.m_pen;
    //TODO animate dash pattern also
    //    if (stroke->m_dashPattern.m_keyframes.size())
    //        m_dashPattern = stroke->m_dashPattern.m_keyframes[0].m_value;
    //    m_is_static = m_color->is_static() and
    //            m_opacity->is_static() and
    //            m_width->is_static();
}

bool StrokeNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_color->update(t);
    //        m_opacity->update(t);
    //        m_width->update(t);

    //        qreal width = m_width->value();
    //        m_pen.setColor(to_color(m_color->value()));
    //        m_pen.setWidthF(width);

    //        if (m_dashPattern.size())
    //        {
    //            QVector<qreal> dashes;
    //            dashes << (m_dashPattern[0].m_value.m_keyframes[0].m_value + 0.0000001)/width;
    //            dashes << (m_dashPattern[1].m_value.m_keyframes[0].m_value + 0.0000001)/width;
    //            m_pen.setDashPattern(dashes);
    //            m_pen.setDashOffset(m_dashPattern[2].m_value.m_keyframes[0].m_value/width);
    //        }
    //    }
    return result;
}

void StrokeNode::render(QPainter *painter)
{
    painter->save();
    painter->setPen(m_pen);
    //TODO opacity

    //    QPainterPath path;
    //    for (auto path_node : m_pathNodes) {
    //        path.addPath(path_node->path());
    //    }

    //    if (not path.isEmpty())
    //        painter->drawPath(path);

    painter->restore();
}

}
