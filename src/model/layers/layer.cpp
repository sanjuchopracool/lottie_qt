#include "layer.h"

namespace eao {

namespace {
const QString name_key = "nm";
const QString index_key = "ind";
const QString type_key = "ty";
const QString coordinate_space_key = "ddd";
const QString in_frame_key = "ip";
const QString out_frame_key = "op";
const QString start_time_key = "st";
const QString transform_key = "ks";
const QString parent_key = "parent";
const QString blend_mode_key = "bm";
const QString masks_key = "masksProperties";
const QString time_stretch_key = "sr";
const QString matte_key = "tt";
const QString hidden_key = "hd";
const QStringView auto_orient_key = u"ao";
}

Layer::Layer() {}

Layer::~Layer() {}

void Layer::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_name = in_obj.take(name_key).toString();
    m_index = in_obj.take(index_key).toInt();
    m_type = static_cast<LayerType>(in_obj.take(type_key).toInt());
    Q_ASSERT(CoordinateSpace::Type2D
             == static_cast<CoordinateSpace>(in_obj.take(coordinate_space_key).toInt()));
    m_in_point = in_obj.take(in_frame_key).toDouble();
    m_out_point = in_obj.take(out_frame_key).toDouble();
    m_start_time = in_obj.take(start_time_key).toDouble();
    auto tr = in_obj.take(transform_key).toObject();
    m_transform.decode(tr, out_messages);

    m_parent_index = in_obj.take(parent_key).toInt(-1);
    if (m_parent_index != -1) {
        static bool msg = true;
        if (msg) {
            msg = false;
            out_messages.emplaceBack(QString("Warning: Layer parenting is not fully supported yet!"));
        }
    }

    m_blend_mode = static_cast<BlendMode>(in_obj.take(blend_mode_key).toInt());
    if (m_blend_mode != BlendMode::Normal) {
        out_messages.emplaceBack("Error: Layer blender mode are not supported yet!");
    }
    //masks
    m_time_stretch = in_obj.take(time_stretch_key).toDouble(1.0);
    m_matte = static_cast<MatteType>(in_obj.take(matte_key).toInt(0));
    if (m_matte != MatteType::None) {
        out_messages.emplaceBack("Error: Layer matte type is not supported yet!");
    }
    m_hidden = in_obj.take(hidden_key).toBool();

    if (in_obj.take(auto_orient_key).toInt()) {
        out_messages.emplaceBack("Error: Layer auto orient are not supported yet!");
    }

    for(const auto& element : in_obj.keys()) {
        const static QString msg("Error: Unsupproted element : %1 in layer");
        out_messages.emplace_back(msg.arg(element));
    }
}

bool Layer::in_range(FrameType t) const
{
    return (m_in_point <= t) and (t <= m_out_point);
}

}
