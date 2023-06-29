#include "EllipseNode.h"

#include "Model/ShapeItems/Ellipse.h"

namespace eao {
EllipseNode::EllipseNode(const Ellipse &ellipse)
    : m_size(ellipse.m_size->create_animator(this))
    , m_position(ellipse.m_position->create_animator(this))
{
}

bool EllipseNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_size->update(t);
    //        m_position->update(t);

    //        m_ellipse_path = QPainterPath();
    //        auto size = m_size->value();
    //        auto position = m_position->value();

    //        QRectF rect;
    //        rect.setSize(QSizeF(size.x(), size.y()));
    //        rect.moveCenter({position.x(), position.y()});
    //        m_ellipse_path.addEllipse(rect);
    //    }
    //    m_path = m_ellipse_path;
    return result;
}
}
