#include "FillNode.h"

#include "../..//NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include "../../Model/ShapeItems/Fill.h"

#include <QPainter>

namespace Lottie {

FillNode::FillNode(const Fill *fill)
{
    using PropColor = NodeProperty<QVector4D>;
    using Prop1D = NodeProperty<Vector1D>;
    using KFVPCOLOR = KeyFrameValueProvider<QVector4D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_color = std::make_unique<PropColor>(new KFVPCOLOR(fill->m_color));
    m_opacity = std::make_unique<Prop1D>(new KFVP1D(fill->m_opacity));

    m_is_static = m_color->is_static() && m_opacity->is_static();
}

bool FillNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_color->needs_update(t) or m_opacity->needs_update(t);
}

bool FillNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_color->update(t);
    }
    return result;
}

void FillNode::render(QPainter *painter)
{
    painter->save();
    painter->setBrush(to_color(m_color->value()));
        //TODO opacity

    QPainterPath path;
    for(auto pathNode : m_pathNodes)
    {
        path.addPath(pathNode->path());
    }

    if (not path.isEmpty())
        painter->drawPath(path);

    painter->restore();
}

}
