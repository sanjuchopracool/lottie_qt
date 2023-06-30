#include "fill_node.h"

#include "Model/ShapeItems/Fill.h"
#include <QPainter>

namespace eao {

FillNode::FillNode(const Fill &fill)
    : m_fill(fill)
    , m_color(fill.m_color->create_animator(this))
    , m_opacity(fill.m_opacity->create_animator(this))
{
    // TODO FILL group and composite
}

bool FillNode::update(FrameType t, bool force_update)
{
    m_dirty = false;
    m_color->update(t);
    m_opacity->update(t);
    return m_dirty;
}

void FillNode::set_content(const std::vector<ShapeItemNode *> &,
                           const std::vector<ShapeItemNode *> &items_after)
{
    for (const ShapeItemNode *node : items_after) {
        auto *path_node = dynamic_cast<const PathNode *>(node);
        if (path_node)
            m_paths.emplace_back(path_node);
    }
}

void FillNode::draw(QPainter *painter, int parent_alpha)
{
    if (m_fill.m_hidden)
        return;

    QColor color(to_color(m_color->value()));
    int opacity(m_opacity->value());

    if (color.alpha() == 0 || opacity == 0)
        return;

    //TODO layers above are filled multiple times
    QPainterPath path;
    for (auto *item : m_paths) {
        path.addPath(item->path());
    }

    if (!path.isEmpty()) {
        painter->setPen(Qt::NoPen);
        int alpha = (parent_alpha * color.alpha() * opacity) / (255 * 100);
        color.setAlpha(alpha);
        painter->setBrush(color);
        painter->drawPath(path);
    }
}

//void FillNode::render(QPainter *painter)
//{
//    painter->save();
//    painter->setBrush(to_color(m_color->value()));
//    //TODO opacity

//    //    QPainterPath path;
//    //    for (auto path_node : m_pathNodes) {
//    //        path.addPath(path_node->path());
//    //    }

//    //    if (not path.isEmpty())
//    //        painter->drawPath(path);

//    painter->restore();
//}

} // namespace eao
