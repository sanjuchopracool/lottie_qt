#include "TransformationNode.h"

#include "../../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"
#include "../../Utility/Primitives/Transformation.h"

#include <QPainter>

namespace Lottie {

TransformationNode::TransformationNode(const Transformation &transformation)
{
    using Prop3D = NodeProperty<QVector3D>;
    using Prop1D = NodeProperty<Vector1D>;
    using KFVP3D = KeyFrameValueProvider<QVector3D>;
    using KFVP1D = KeyFrameValueProvider<Vector1D>;

    m_anchor = std::make_unique<Prop3D>(new KFVP3D(transformation.m_anchor));
    m_position = std::make_unique<Prop3D>(new KFVP3D(transformation.m_position));
    m_scale = std::make_unique<Prop3D>(new KFVP3D(transformation.m_scale));

    m_rotation = std::make_unique<Prop1D>(new KFVP1D(transformation.m_rotation));
    m_opacity = std::make_unique<Prop1D>(new KFVP1D(transformation.m_opacity));
    m_skew = std::make_unique<Prop1D>(new KFVP1D(transformation.m_skew));
    m_skew_axis = std::make_unique<Prop1D>(new KFVP1D(transformation.m_skew_axis));

    m_is_static = m_anchor->is_static() and m_position->is_static() and m_scale->is_static() and
            m_rotation->is_static() and m_opacity->is_static() and m_skew->is_static() and m_skew_axis->is_static();
}

bool TransformationNode::need_update(FrameType t) const
{
    if (m_is_static)
        return false;

//    if (m_parent_transformation and m_parent_transformation->need_update(t))
//        return true;

    return m_anchor->needs_update(t) or
            m_position->needs_update(t) or
            m_rotation->needs_update(t) or
            m_scale->needs_update(t) or
            m_opacity->needs_update(t) or
            m_skew->needs_update(t) or
            m_skew_axis->needs_update(t);
}

bool TransformationNode::update(FrameType t, bool force_update)
{
    bool result = false;
    if (force_update or need_update(t))
    {
        update_transform(t);
        result = true;
    }

    return result;
}

void TransformationNode::update(FrameType t, QPainter *painter)
{
    update_transform(t);
    update_painter(painter);
}

void TransformationNode::update_painter(QPainter *painter)
{
    painter->setTransform(tranform(), true);
}

void TransformationNode::update_transform(FrameType t)
{
    m_anchor->update(t);
    m_position->update(t);
    m_rotation->update(t);
    m_scale->update(t);
    m_opacity->update(t);
    m_skew->update(t);
    m_skew_axis->update(t);
}

void TransformationNode::set_parent_transform(const TransformationNode *parent_transform)
{
    m_parent_transformation = parent_transform;
//    if (m_parent_transformation)
//    {
//        m_is_static = m_is_static and m_parent_transformation->is_static();
//    }
}

QTransform TransformationNode::tranform() const
{
    auto anchor = m_anchor->value();
    auto pos = m_position->value();
    auto rotation = m_rotation->value();
    auto scale = m_scale->value()/100;

//TODO other properties

    QTransform tr;
    tr.translate(pos.x(), pos.y());
//    tr.translate(anchor.x(), anchor.y());
    tr.rotate(rotation);
    tr.scale(scale.x(), scale.y());
    tr.translate(-anchor.x(), - anchor.y());

    if (m_parent_transformation)
        tr *= m_parent_transformation->tranform();

    return tr;
}

}
