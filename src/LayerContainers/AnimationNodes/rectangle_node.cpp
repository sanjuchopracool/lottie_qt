#include "rectangle_node.h"

#include "../../Model/ShapeItems/rectangle.h"
#include "../../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"

namespace eao {
RectangleNode::RectangleNode(const eao::Rectangle *rectangle)
{
    using Prop2D = NodeProperty<QVector2D>;
    using KFVP2D = KeyFrameValueProvider<QVector2D>;

    m_size = std::make_unique<Prop2D>(new KFVP2D(rectangle->m_size));
    m_center = std::make_unique<Prop2D>(new KFVP2D(rectangle->m_center));
    m_corner_radius = std::make_unique<Prop2D>(new KFVP2D(rectangle->m_corner_radius));
    m_is_static = m_size->is_static() and m_center->is_static() and m_corner_radius->is_static();
}

bool RectangleNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_center->needs_update(t) or m_size->needs_update(t);
}

bool RectangleNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_size->update(t);
        m_center->update(t);

        m_rectangle_path = QPainterPath();
        auto size = m_size->value();
        auto center = m_center->value();
        auto radius = m_center->value();

        QRectF rect;
        rect.setSize(QSizeF(size.x(), size.y()));
        rect.moveCenter({center.x(), center.y()});
        m_rectangle_path.addRoundedRect(rect, radius.x(), radius.y());
    }
    m_path = m_rectangle_path;
    return result;
}
}
