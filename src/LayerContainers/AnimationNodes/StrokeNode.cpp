#include "StrokeNode.h"

#include "Model/ShapeItems/Stroke.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include <QPainter>

namespace eao {
StrokeNode::StrokeNode(const Stroke* stroke)
{
    using PropColor = NodeProperty<QVector4D>;
    using Prop1D = NodeProperty<Vector1D>;
    using KFVPCOLOR = KeyFrameValueProvider<QVector4D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_pen = stroke->m_pen;
    m_color = std::make_unique<PropColor>(new KFVPCOLOR(stroke->m_color));
    m_opacity = std::make_unique<Prop1D>(new KFVP1D(stroke->m_opacity));
    m_width = std::make_unique<Prop1D>(new KFVP1D(stroke->m_width));

    //TODO animate dash pattern also
    if (stroke->m_dashPattern.m_keyframes.size())
        m_dashPattern = stroke->m_dashPattern.m_keyframes[0].m_value;
    m_is_static = m_color->is_static() and
            m_opacity->is_static() and
            m_width->is_static();
}

bool StrokeNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_color->needs_update(t) or m_opacity->needs_update(t) or m_width->needs_update(t);
}

bool StrokeNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_color->update(t);
        m_opacity->update(t);
        m_width->update(t);

        qreal width = m_width->value();
        m_pen.setColor(to_color(m_color->value()));
        m_pen.setWidthF(width);

        if (m_dashPattern.size())
        {
            QVector<qreal> dashes;
            dashes << (m_dashPattern[0].m_value.m_keyframes[0].m_value + 0.0000001)/width;
            dashes << (m_dashPattern[1].m_value.m_keyframes[0].m_value + 0.0000001)/width;
            m_pen.setDashPattern(dashes);
            m_pen.setDashOffset(m_dashPattern[2].m_value.m_keyframes[0].m_value/width);
        }
    }
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
