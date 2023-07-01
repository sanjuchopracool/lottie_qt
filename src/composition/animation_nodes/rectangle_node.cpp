#include "rectangle_node.h"

#include "model/shape_items/rectangle.h"
#include <utility/primitives/utility.h>

namespace eao {
RectangleNode::RectangleNode(const eao::Rectangle &rectangle)
    : m_rectangle(rectangle)
    , m_size(rectangle.size()->create_animator(this))
    , m_center(rectangle.center()->create_animator(this))
    , m_corner_radius(rectangle.corner_radius()->create_animator(this))
{
}

bool RectangleNode::update(FrameType t, bool force_update)
{
    bool result = false;
    m_size->update(t);
    m_center->update(t);
    m_corner_radius->update(t);

    // TODO listen to trim paths also
    if (force_update || m_dirty) {
        create_path();
        m_dirty = false;
        result = true;
    }
    return result;
}

void RectangleNode::create_path()
{
    m_path.clear();

    if (m_rectangle.hidden()) {
        return;
    }

    QVector2D size = m_size->value();
    QVector2D position = m_center->value();
    qreal hw = size.x() / 2.f;
    qreal hh = size.y() / 2.f;
    qreal r = m_corner_radius->value();

    auto radius_rect = [&](QPointF center) -> QRectF {
        QRectF rect(QPointF{-r, -r}, QPointF{r, r});
        rect.moveCenter(center);
        return rect;
    };

    m_path.moveTo(hw, -(hh - r));
    if (m_rectangle.direction() == PathDirection::CounterClockwise) {
        QRectF rect = radius_rect(QPointF((hw - r), -(hh - r)));
        m_path.arcTo(rect, 0, 90);
        m_path.lineTo(-(hw - r), -hh);
        rect = radius_rect(QPointF(-(hw - r), -(hh - r)));
        m_path.arcTo(rect, 90, 90);
        m_path.lineTo(-hw, (hh - r));
        rect = radius_rect(QPointF(-(hw - r), hh - r));
        m_path.arcTo(rect, 180, 90);
        m_path.lineTo(hw - r, hh);
        rect = radius_rect(QPointF(hw - r, hh - r));
        m_path.arcTo(rect, 270, 90);
    } else {
        m_path.lineTo(hw, (hh - r));
        QRectF rect = radius_rect(QPointF(hw - r, hh - r));
        m_path.arcTo(rect, 0, -90);
        m_path.lineTo(-(hw - r), hh);
        rect = radius_rect(QPointF(-(hw - r), hh - r));
        m_path.arcTo(rect, -90, -90);
        m_path.lineTo(-hw, -(hh - r));
        rect = radius_rect(QPointF(-(hw - r), -(hh - r)));
        m_path.arcTo(rect, -180, -90);
        m_path.lineTo(hw - r, -hh);
        rect = radius_rect(QPointF((hw - r), -(hh - r)));
        m_path.arcTo(rect, -270, -90);
    }
    m_path.closeSubpath();

    m_path.translate(position.x(), position.y());
    apply_trim();
}
} // namespace eao
