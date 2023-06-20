#include "Animation.h"
#include "Layers/LayerFactory.h"

#include <QJsonArray>

using namespace std;
namespace Lottie {

namespace {
const QString version_key("v");
const QString type_key("ddd");
const QString start_frame_key("ip");
const QString end_frame_key("op");
const QString framerate_key("fr");
const QString width_key("w");
const QString height_key("h");
const QString layers_key("layers");
const QString glyphs_key("chars");
const QString fonts_key("fonts");
const QString asset_library_key("assets");
const QString markers_key("markers");

QList<LayerModel*> load_layers(const QJsonObject& in_obj)
{
    QList<LayerModel*> result;
    const auto& layers = in_obj.value(layers_key).toArray();
    for(const auto& layer_value : layers)
    {
        auto layer = layer_from_object(layer_value.toObject());
        if (layer)
            result.append(layer);
    }
    return  result;
}

}

Animation::Animation()
{

}

Animation::~Animation()
{
    qDeleteAll(m_layers);
}

void Animation::decode(const QJsonObject &in_obj)
{
    m_version = in_obj.value(version_key).toString();

    m_type = static_cast<CoordinateSpace>(in_obj.value(type_key).toInt());
    Q_ASSERT(m_type == CoordinateSpace::Type2D);

    m_start_frame = in_obj.value(start_frame_key).toDouble();
    m_end_frame = in_obj.value(end_frame_key).toDouble();
    m_frame_rate = in_obj.value(framerate_key).toDouble();

    m_width = in_obj.value(width_key).toInt();
    m_height = in_obj.value(height_key).toInt();

    m_layers = load_layers(in_obj);
}


}
