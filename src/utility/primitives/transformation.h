#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "utility.h"
#include <model/property_system/property.h>

namespace eao {

struct LayerTransformation
{
    void decode(QJsonObject &in_obj, QList<QString> &out_messages);

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
