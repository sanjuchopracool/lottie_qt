#include "ellipse_node.h"

#include "Model/ShapeItems/Ellipse.h"

namespace eao {
EllipseNode::EllipseNode(const Ellipse &ellipse)
    : m_size(ellipse.m_size->create_animator(this))
    , m_position(ellipse.m_position->create_animator(this))
{
}

bool EllipseNode::update(FrameType t, bool force_update)
{
    m_dirty = false;
    m_size->update(t);
    m_position->update(t);

    if (force_update || m_dirty) {
        m_path.clear();
        auto size = m_size->value();
        auto position = m_position->value();

        QRectF rect;
        rect.setSize(QSizeF(size.x(), size.y()));
        rect.moveCenter({position.x(), position.y()});
        m_path.addEllipse(rect);
    }
    return m_dirty;
}
}
