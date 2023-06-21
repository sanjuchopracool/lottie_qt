#include "composition.h"
#include "Layers/LayerFactory.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

using namespace std;
namespace eao {

namespace {
const QStringView version_key(u"v");
const QStringView type_key(u"ddd");
const QStringView in_point_key(u"ip");
const QStringView out_point_key(u"op");
const QStringView framerate_key(u"fr");
const QStringView width_key(u"w");
const QStringView height_key(u"h");
const QStringView layers_key(u"layers");
//const QStringView glyphs_key(u"chars");
//const QStringView fonts_key(u"fonts");
//const QStringView asset_library_key(u"assets");
//const QStringView markers_key(u"markers");

QList<LayerModel *> load_layers(const QJsonObject &in_obj , QList<QString> &out_messages)
{
    QList<LayerModel *> result;
    const auto &layers = in_obj.value(layers_key).toArray();
    for (const auto &layer_value : layers) {
        auto layer = layer_from_object(layer_value.toObject() , out_messages);
        if (layer)
            result.append(layer);
    }
    return result;
}

} // namespace

Composition::Composition() {}

Composition::~Composition()
{
    qDeleteAll(m_layers);
}

void Composition::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    out_messages.clear();
    m_version = in_obj.take(version_key).toString();

    m_type = static_cast<CoordinateSpace>(in_obj.take(type_key).toInt());
    Q_ASSERT(m_type == CoordinateSpace::Type2D);

    auto val = in_obj.take(in_point_key);
    Q_ASSERT(!val.isUndefined());
    m_in_point = val.toDouble();

    val = in_obj.take(out_point_key);
    Q_ASSERT(!val.isUndefined());
    m_out_point = val.toDouble();

    val = in_obj.take(framerate_key);
    Q_ASSERT(!val.isUndefined());
    m_framerate = val.toDouble();

    val = in_obj.take(width_key);
    Q_ASSERT(!val.isUndefined());
    m_width = val.toInt();

    val = in_obj.take(height_key);
    Q_ASSERT(!val.isUndefined());
    m_height = val.toInt();

    m_layers = load_layers(in_obj , out_messages);
}

} // namespace eao
