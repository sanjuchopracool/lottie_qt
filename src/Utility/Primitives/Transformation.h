#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "Utility.h"

namespace eao {

class Transformation3D
{
public:

    virtual void decode(QJsonObject &in_obj, QList<QString> &out_messages);

public:
    KeyFrameGroup<QVector3D> m_anchor;
    KeyFrameGroup<QVector3D> m_position;
    KeyFrameGroup<QVector3D> m_scale;
    KeyFrameGroup<Vector1D> m_rotation;
    KeyFrameGroup<int> m_opacity;
    KeyFrameGroup<Vector1D> m_skew;
    KeyFrameGroup<Vector1D> m_skew_axis;
};

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


}

#endif // SHAPETRANSFORMATION_H
