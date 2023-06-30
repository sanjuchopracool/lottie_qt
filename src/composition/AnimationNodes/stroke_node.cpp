#include "stroke_node.h"

#include "Model/ShapeItems/Stroke.h"
#include "path_node.h"
#include "trim_node.h"
#include <QPainter>

namespace eao {

class PathGroup
{
public:
    PathGroup(TrimNode *trim)
        : m_trim(trim)
    {}

private:
    TrimNode *m_trim;
};

StrokeNode::StrokeNode(const Stroke &stroke)
    : m_stroke(stroke)
    , m_color(stroke.m_color->create_animator(this))
    , m_opacity(stroke.m_opacity->create_animator(this))
    , m_width(stroke.m_width->create_animator(this))
{
    //    m_pen = stroke.m_pen;
    //TODO animate dash pattern also
    //    if (stroke->m_dashPattern.m_keyframes.size())
    //        m_dashPattern = stroke->m_dashPattern.m_keyframes[0].m_value;
    //    m_is_static = m_color->is_static() and
    //            m_opacity->is_static() and
    //            m_width->is_static();
}

bool StrokeNode::update(FrameType t, bool force_update)
{
    bool m_dirty = false;
    m_color->update(t);
    m_opacity->update(t);
    m_width->update(t);

    //    if (force_update or need_update(t))
    //    {
    //        result = true;

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
    return m_dirty;
}

void StrokeNode::set_content(const std::vector<ShapeItemNode *> &,
                             const std::vector<ShapeItemNode *> &items_after)
{
    for (const ShapeItemNode *node : items_after) {
        auto *path_node = dynamic_cast<const PathNode *>(node);
        if (path_node)
            m_paths.emplace_back(path_node);
    }
}

void StrokeNode::draw(QPainter *painter, int parent_alpha)
{
    if (m_stroke.hidden())
        return;

    QColor color(to_color(m_color->value()));
    int opacity(m_opacity->value());
    qreal width = m_width->value();

    if (color.alpha() == 0 || opacity == 0 || width <= 0.0f)
        return;

    //TODO layers above are filled multiple times
    QPainterPath path;
    for (auto *item : m_paths) {
        path.addPath(item->path());
    }

    if (!path.isEmpty()) {
        painter->setBrush(Qt::NoBrush);
        int alpha = (parent_alpha * color.alpha() * opacity) / (255 * 100);
        color.setAlpha(alpha);
        QPen pen;
        pen.setColor(color);
        pen.setWidthF(width);
        painter->setPen(pen);
        painter->drawPath(path);
    }
}

//void StrokeNode::render(QPainter *painter)
//{
//    painter->save();
//    painter->setPen(m_pen);
//    //TODO opacity

//    //    QPainterPath path;
//    //    for (auto path_node : m_pathNodes) {
//    //        path.addPath(path_node->path());
//    //    }

//    //    if (not path.isEmpty())
//    //        painter->drawPath(path);

//    painter->restore();
//}
}
