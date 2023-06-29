#include "ShapeTransformationNode.h"

#include "Model/ShapeItems/ShapeTransformation.h"

#include <QPainter>

namespace eao {

ShapeTransformationNode::ShapeTransformationNode(const ShapeTransformation &transformation)
    : m_anchor(transformation.m_anchor->create_animator(this))
    , m_position(transformation.m_position->create_animator(this))
    , m_scale(transformation.m_scale->create_animator(this))
    , m_rotation(transformation.m_rotation->create_animator(this))
    , m_opacity(transformation.m_opacity->create_animator(this))
    , m_skew(transformation.m_skew->create_animator(this))
    , m_skew_axis(transformation.m_skew_axis->create_animator(this))
{
}

bool ShapeTransformationNode::update(FrameType t, bool force_update)
{
    bool result = false;
    //    if (force_update or need_update(t))
    //    {
    //        result = true;
    //        m_anchor->update(t);
    //        m_position->update(t);
    //        m_rotation->update(t);
    //        m_scale->update(t);
    //        m_opacity->update(t);
    //        m_skew->update(t);
    //        m_skew_axis->update(t);
    //    }

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
