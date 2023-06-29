#include "rectangle_node.h"

#include "Model/ShapeItems/rectangle.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include "Utility/Primitives/Utility.h"

namespace eao {
RectangleNode::RectangleNode(const eao::Rectangle &rectangle)
    : m_size(rectangle.m_size->create_animator(this))
    , m_center(rectangle.m_center->create_animator(this))
    , m_corner_radius(rectangle.m_corner_radius->create_animator(this))
{
}

bool RectangleNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_size->update(t);
    //        m_center->update(t);

    //        m_rectangle_path = QPainterPath();
    //        auto size = m_size->value();
    //        auto center = m_center->value();
    //        auto radius = m_center->value();

    //        QRectF rect;
    //        rect.setSize(QSizeF(size.x(), size.y()));
    //        rect.moveCenter({center.x(), center.y()});
    //        m_rectangle_path.addRoundedRect(rect, radius.x(), radius.y());
    //    }
    //    m_path = m_rectangle_path;
    return result;
}
}
