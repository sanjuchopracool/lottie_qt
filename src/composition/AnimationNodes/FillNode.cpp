#include "FillNode.h"

#include "Model/ShapeItems/Fill.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"

#include <QPainter>

namespace eao {

FillNode::FillNode(const Fill &fill)
    : m_color(fill.m_color->create_animator(this))
    , m_opacity(fill.m_opacity->create_animator(this))
{
}

bool FillNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t)) {
    //        result = true;
    //        m_color->update(t);
    //    }
    return result;
}

void FillNode::render(QPainter *painter)
{
    painter->save();
    painter->setBrush(to_color(m_color->value()));
    //TODO opacity

    //    QPainterPath path;
    //    for (auto path_node : m_pathNodes) {
    //        path.addPath(path_node->path());
    //    }

    //    if (not path.isEmpty())
    //        painter->drawPath(path);

    painter->restore();
}

} // namespace eao
