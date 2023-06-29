#ifndef LAYER_H
#define LAYER_H

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

class Layer
{
public:
    Layer();
    virtual ~Layer();

    virtual void decode(QJsonObject& in_obj, QList<QString> &out_messages);

    bool in_range(FrameType t) const;

    LayerType layer_type() const { return m_type; }
    FrameType in_point() const { return m_in_point; }
    FrameType out_point() const { return m_out_point; }
    FrameType start_time() const { return m_start_time; }

public:
    QString m_name;
    int m_index;
    LayerType m_type;
    FrameType m_in_point;
    FrameType m_out_point;
    FrameType m_start_time;
    LayerTransformation m_transform;
    int m_parent_index = -1;
    BlendMode m_blend_mode;
    // array masks
    double m_time_stretch;
    MatteType m_matte;
    bool m_hidden = false;
};

}

#endif // LAYER_H
