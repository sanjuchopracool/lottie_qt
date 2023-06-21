#include "LayerModel.h"

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
}

LayerModel::LayerModel()
{

}

LayerModel::~LayerModel()
{

}

void LayerModel::decode(const QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_name = in_obj.value(name_key).toString();
    m_index = in_obj.value(index_key).toInt();
    m_type = static_cast<LayerType>(in_obj.value(type_key).toInt());
    m_coordinate_space = static_cast<CoordinateSpace>(in_obj.value(coordinate_space_key).toInt());
    m_in_frame = in_obj.value(in_frame_key).toDouble();
    m_out_frame = in_obj.value(out_frame_key).toDouble();
    m_start_time = in_obj.value(start_time_key).toDouble();
    m_transform.decode(in_obj.value(transform_key).toObject());
    m_parent_index = in_obj.value(parent_key).toInt(-1);
    m_blend_mode = static_cast<BlendMode>(in_obj.value(blend_mode_key).toInt());
    //masks
    m_time_stretch = in_obj.value(time_stretch_key).toDouble(1.0);
    m_matte = static_cast<MatteType>(in_obj.value(matte_key).toInt());
    m_hidden = in_obj.value(hidden_key).toBool();
}

bool LayerModel::in_range(FrameType t) const
{
    return (m_in_frame <= t) and (t <= m_out_frame);
}

}
