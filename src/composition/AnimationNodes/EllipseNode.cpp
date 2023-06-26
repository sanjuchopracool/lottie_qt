#include "EllipseNode.h"

#include "Model/ShapeItems/Ellipse.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"

namespace eao {
EllipseNode::EllipseNode(const Ellipse *ellipse)
{
    using Prop2D = NodeProperty<QVector2D>;
    using KFVP2D = KeyFrameValueProvider<QVector2D>;

    m_size = std::make_unique<Prop2D>(new KFVP2D(ellipse->m_size));
    m_position = std::make_unique<Prop2D>(new KFVP2D(ellipse->m_position));
    m_is_static = m_size->is_static() and m_position->is_static();
}

bool EllipseNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_position->needs_update(t) or m_size->needs_update(t);
}

bool EllipseNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_size->update(t);
        m_position->update(t);

        m_ellipse_path = QPainterPath();
        auto size = m_size->value();
        auto position = m_position->value();

        QRectF rect;
        rect.setSize(QSizeF(size.x(), size.y()));
        rect.moveCenter({position.x(), position.y()});
        m_ellipse_path.addEllipse(rect);
    }
    m_path = m_ellipse_path;
    return result;
}
}
