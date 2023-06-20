#include "ShapeTransformationNode.h"

#include "../../Model/ShapeItems/ShapeTransformation.h"
#include "../../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"

#include <QPainter>

namespace Lottie {

ShapeTransformationNode::ShapeTransformationNode(const ShapeTransformation* transform)
    : m_transform(transform)
{
    using Prop2D = NodeProperty<QVector2D>;
    using Prop1D = NodeProperty<Vector1D>;
    using KFVP2D = KeyFrameValueProvider<QVector2D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_anchor = std::make_unique<Prop2D>(new KFVP2D(m_transform->m_anchor));
    m_position = std::make_unique<Prop2D>(new KFVP2D(m_transform->m_position));
    m_scale = std::make_unique<Prop2D>(new KFVP2D(m_transform->m_scale));

    m_rotation = std::make_unique<Prop1D>(new KFVP1D(m_transform->m_rotation));
    m_opacity = std::make_unique<Prop1D>(new KFVP1D(m_transform->m_opacity));
    m_skew = std::make_unique<Prop1D>(new KFVP1D(m_transform->m_skew));
    m_skew_axis = std::make_unique<Prop1D>(new KFVP1D(m_transform->m_skew_axis));

    m_is_static = m_anchor->is_static() and m_position->is_static() and m_scale->is_static() and
            m_rotation->is_static() and m_opacity->is_static() and m_skew->is_static() and m_skew_axis->is_static();
}

bool ShapeTransformationNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

    return m_anchor->needs_update(t) or
            m_position->needs_update(t) or
            m_rotation->needs_update(t) or
            m_scale->needs_update(t) or
            m_opacity->needs_update(t) or
            m_skew->needs_update(t) or
            m_skew_axis->needs_update(t);
}

bool ShapeTransformationNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        result = true;
        m_anchor->update(t);
        m_position->update(t);
        m_rotation->update(t);
        m_scale->update(t);
        m_opacity->update(t);
        m_skew->update(t);
        m_skew_axis->update(t);
    }

    return result;
}

void ShapeTransformationNode::render(QPainter *painter)
{
    auto anchor = m_anchor->value();
    auto pos = m_position->value();
    auto rotation = m_rotation->value();
    auto scale = m_scale->value()/100;

    // TODO other proeprties

    QTransform tr;
    tr.translate(pos.x(), pos.y());
    tr.rotate(rotation);
    tr.scale(scale.x(), scale.y());
    tr.translate(-anchor.x(), - anchor.y());
    painter->setTransform(tr, true);
}

}
