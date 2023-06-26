#ifndef LAYERMODEL_H
#define LAYERMODEL_H

#include "Utility/Primitives/Transformation.h"
#include "lottielib.h"
#include <QJsonObject>

namespace eao {

enum class LayerType { Precomp, Solid, Image, Null, Shape, Text };
const QList<QStringView> layer_type_names {u"Precomp", u"Solid", u"Image", u"Null", u"Shape", u"Text" };

enum class MatteType { None, Add, Invert, Unknown };

enum class BlendMode
{
    Normal,
    Multiply,
    Screen,
    Overlay,
    Darken,
    Lighten,
    ColorBurn,
    HardLight,
    SoftLight,
    Difference,
    Exclusion,
    Hue,
    Saturation,
    Color,
    Luminosity
};

class LayerModel
{
public:
    LayerModel();
    virtual ~LayerModel();

    virtual void decode(QJsonObject& in_obj, QList<QString> &out_messages);

    bool in_range(FrameType t) const;
public:
    QString m_name;
    int m_index;
    LayerType m_type;
    CoordinateSpace m_coordinate_space;
    FrameType m_in_frame;
    FrameType m_out_frame;
    FrameType m_start_time;
    Transformation3D m_transform;
    int m_parent_index = -1;
    BlendMode m_blend_mode;
    // array masks
    double m_time_stretch;
    MatteType m_matte;
    bool m_hidden = false;
};

}

#endif // LAYERMODEL_H
