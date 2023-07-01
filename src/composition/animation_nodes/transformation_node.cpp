#include "transformation_node.h"

#include "utility/primitives/transformation.h"

#include <QPainter>
#include <QVector2D>

namespace eao {

LayerTransformationNode::LayerTransformationNode(const LayerTransformation &transformation)
    : m_anchor(transformation.m_anchor->create_animator(this))
    , m_position(transformation.m_position->create_animator(this))
    , m_scale(transformation.m_scale->create_animator(this))
    , m_rotation(transformation.m_rotation->create_animator(this))
    , m_opacity(transformation.m_opacity->create_animator(this))
    , m_skew(transformation.m_skew->create_animator(this))
    , m_skew_axis(transformation.m_skew_axis->create_animator(this))

{}

bool LayerTransformationNode::update(FrameType t, bool force_update)
{
    m_dirty = false;
    update_transform(t);
    return m_dirty;
}

void LayerTransformationNode::update_transform(FrameType t)
{
    m_anchor->update(t);
    m_position->update(t);
    m_rotation->update(t);
    m_scale->update(t);
    m_opacity->update(t);
    m_skew->update(t);
    m_skew_axis->update(t);
}

QTransform LayerTransformationNode::transform() const
{
    auto anchor = m_anchor->value();
    auto pos = m_position->value();
    auto rotation = m_rotation->value();
    auto scale = m_scale->value() / 100;

    //TODO other properties

    QTransform tr;
    tr.translate(pos.x(), pos.y());
    //    tr.translate(anchor.x(), anchor.y());
    tr.rotate(rotation);
    tr.scale(scale.x(), scale.y());
    tr.translate(-anchor.x(), -anchor.y());

    if (m_parent_transformation)
        tr *= m_parent_transformation->transform();

    return tr;
}

} // namespace eao
