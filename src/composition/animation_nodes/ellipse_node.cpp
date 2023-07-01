#include "ellipse_node.h"

#include "model/shape_items/ellipse.h"

namespace eao {

constexpr qreal ELLIPSE_CONTROL_POINT_PERCENTAGE = 0.55228f;

EllipseNode::EllipseNode(const Ellipse &ellipse)
    : m_ellipse(ellipse)
    , m_size(ellipse.size()->create_animator(this))
    , m_position(ellipse.position()->create_animator(this))
{
}

bool EllipseNode::update(FrameType t, bool force_update)
{
    bool result = false;
    m_size->update(t);
    m_position->update(t);

    // TODO listen to trim paths also
    if (force_update || m_dirty) {
        create_path();
        m_dirty = false;
        result = true;
    }
    return result;
}

void EllipseNode::create_path()
{
    m_path.clear();

    if (m_ellipse.hidden()) {
        return;
    }

    QVector2D size = m_size->value();
    QVector2D position = m_position->value();
    qreal half_width = size.x() / 2.f;
    qreal half_height = size.y() / 2.f;

    qreal el_w = half_width * ELLIPSE_CONTROL_POINT_PERCENTAGE;
    qreal el_h = half_height * ELLIPSE_CONTROL_POINT_PERCENTAGE;

    if (m_ellipse.direction() == PathDirection::CounterClockwise) {
        m_path.moveTo(0, -half_height);
        m_path.cubicTo(0 - el_w, -half_height, -half_width, 0 - el_h, -half_width, 0);
        m_path.cubicTo(-half_width, 0 + el_h, 0 - el_w, half_height, 0, half_height);
        m_path.cubicTo(0 + el_w, half_height, half_width, 0 + el_h, half_width, 0);
        m_path.cubicTo(half_width, 0 - el_h, 0 + el_w, -half_height, 0, -half_height);
    } else {
        m_path.moveTo(0, -half_height);
        m_path.cubicTo(0 + el_w, -half_height, half_width, 0 - el_h, half_width, 0);
        m_path.cubicTo(half_width, 0 + el_h, 0 + el_w, half_height, 0, half_height);
        m_path.cubicTo(0 - el_w, half_height, -half_width, 0 + el_h, -half_width, 0);
        m_path.cubicTo(-half_width, 0 - el_h, 0 - el_w, -half_height, 0, -half_height);
    }
    m_path.closeSubpath();

    m_path.translate(position.x(), position.y());
    apply_trim();
}
} // namespace eao
