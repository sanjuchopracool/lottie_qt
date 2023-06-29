#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "Utility.h"
#include <Model/property_system/property.h>

namespace eao {

class RepeaterTransformation
{
public:

    virtual void decode(const QJsonObject& in_obj);

public:
    KeyFrameGroup<QVector2D> m_anchor;
    KeyFrameGroup<QVector2D> m_position;
    KeyFrameGroup<QVector2D> m_scale;
    KeyFrameGroup<Vector1D> m_rotation;
    KeyFrameGroup<int> m_opacity;
    KeyFrameGroup<Vector1D> m_skew;
    KeyFrameGroup<Vector1D> m_skew_axis;
};

class LayerTransformation
{
public:
    virtual void decode(QJsonObject &in_obj, QList<QString> &out_messages);

public:
    PropertyPtr<QVector3D> m_anchor;
    PropertyPtr<QVector3D> m_position;
    PropertyPtr<QVector3D> m_scale;
    PropertyPtr<Vector1D> m_rotation;
    PropertyPtr<int> m_opacity;
    PropertyPtr<Vector1D> m_skew;
    PropertyPtr<Vector1D> m_skew_axis;
};
} // namespace eao

#endif // SHAPETRANSFORMATION_H
