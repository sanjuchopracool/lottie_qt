#include "polystar_node.h"

#include "Model/ShapeItems/polystar.h"
#include "NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include <cmath>

namespace eao {
PolyStarNode::PolyStarNode(const PolyStar *polystar)
{
    using Prop1D = NodeProperty<Vector1D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    using Prop2D = NodeProperty<QVector2D>;
    using KFVP2D = KeyFrameValueProvider<QVector2D>;

    m_center = std::make_unique<Prop2D>(new KFVP2D(polystar->m_center));
    m_rotation = std::make_unique<Prop1D>(new KFVP1D(polystar->m_rotation));
    m_outer_radius = std::make_unique<Prop1D>(new KFVP1D(polystar->m_outer_radius));
    m_outer_roundness = std::make_unique<Prop1D>(new KFVP1D(polystar->m_outer_roundness));
    m_inner_radius = std::make_unique<Prop1D>(new KFVP1D(polystar->m_inner_radius));
    m_inner_roundness = std::make_unique<Prop1D>(new KFVP1D(polystar->m_inner_roundness));
    m_num_points = std::make_unique<Prop1D>(new KFVP1D(polystar->m_num_points));
    m_is_static = m_center->is_static() && m_rotation->is_static() && m_outer_radius->is_static()
                  && m_outer_roundness->is_static() && m_inner_radius->is_static() && m_inner_roundness->is_static()
                  && m_num_points->is_static();

}

bool PolyStarNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_center->needs_update(t) && m_rotation->needs_update(t) && m_outer_radius->needs_update(t)
           && m_outer_roundness->needs_update(t) && m_inner_radius->needs_update(t) && m_inner_roundness->needs_update(t)
           && m_num_points->needs_update(t);
}

bool PolyStarNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_center->update(t);
        m_rotation->update(t);
        m_outer_radius->update(t);
        m_outer_roundness->update(t);
        m_inner_radius->update(t);
        m_inner_roundness->update(t);
        m_num_points->update(t);
        
        m_star_path = QPainterPath();
        auto center = m_center->value();
        auto inner_radius = m_inner_radius->value();
        auto outer_radius = m_outer_radius->value();
        auto num_points = m_num_points->value();

        auto half_angle = M_PI/num_points;

//        qDebug() << inner_radius << outer_radius;
        auto angle = half_angle/2;
        auto x1 = inner_radius * std::cosf(angle);
        auto y1 = inner_radius * std::sinf(angle);
        m_star_path.moveTo(x1, y1);
        int i = 0;
        for(; i < num_points - 1; ++i) {
            angle += half_angle;
            auto x2 = outer_radius * std::cosf(angle);
            auto y2 = outer_radius * std::sinf(angle);
            m_star_path.lineTo(x2, y2);

            angle += half_angle;
            auto x1 = inner_radius * std::cosf(angle);
            auto y1 = inner_radius * std::sinf(angle);
            m_star_path.lineTo(x1, y1);
        }
        angle += half_angle;
        auto x2 = outer_radius * std::cosf(angle);
        auto y2 = outer_radius * std::sinf(angle);
        m_star_path.lineTo(x2, y2);
        m_star_path.closeSubpath();
        m_star_path.translate(center.x(), center.y());



    }
    m_path = m_star_path;
    return result;
}
}
