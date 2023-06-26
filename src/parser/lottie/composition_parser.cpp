#include "composition_parser.h"
#include "Model/composition.h"

#include "Model/Layers/LayerFactory.h"
#include "Model/composition.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QStringView>

namespace eao::Lottie {

const QStringView version_key(u"v");
const QStringView type_key(u"ddd");
const QStringView in_point_key(u"ip");
const QStringView out_point_key(u"op");
const QStringView framerate_key(u"fr");
const QStringView width_key(u"w");
const QStringView height_key(u"h");
const QStringView layers_key(u"layers");
const QStringView name_key(u"nm");
//const QStringView glyphs_key(u"chars");
//const QStringView fonts_key(u"fonts");
const QStringView asset_library_key(u"assets");
//const QStringView markers_key(u"markers");

Composition::LayerList load_layers(QJsonObject &in_obj, QList<QString> &out_messages)
{
    Composition::LayerList result;
    auto val = in_obj.take(layers_key);
    Q_ASSERT(!val.isUndefined());
    const auto &layers = val.toArray();
    for (const auto &layer_value : layers) {
        QJsonObject layer_obj = layer_value.toObject();
        auto layer = layer_from_object(layer_obj, out_messages);
        if (layer)
            result.emplace_back(layer);
    }
    return result;
}

std::unique_ptr<Composition> LottieParser::parse(QJsonObject &in_obj, QList<QString> &out_messages)
{
    QString version = in_obj.take(version_key).toString();
    QString name = in_obj.take(name_key).toString();

    CoordinateSpace type = static_cast<CoordinateSpace>(in_obj.take(type_key).toInt());
    Q_ASSERT(type == CoordinateSpace::Type2D);

    auto val = in_obj.take(in_point_key);
    Q_ASSERT(!val.isUndefined());
    FrameType in_point = val.toDouble();

    val = in_obj.take(out_point_key);
    Q_ASSERT(!val.isUndefined());
    FrameType out_point = val.toDouble();

    val = in_obj.take(framerate_key);
    Q_ASSERT(!val.isUndefined());
    FrameType framerate = val.toDouble();

    val = in_obj.take(width_key);
    Q_ASSERT(!val.isUndefined());
    int width = val.toInt();

    val = in_obj.take(height_key);
    Q_ASSERT(!val.isUndefined());
    int height = val.toInt();

    auto comp = std::make_unique<eao::Composition>(std::move(name),
                                                   std::move(version),
                                                   width,
                                                   height,
                                                   in_point,
                                                   out_point,
                                                   framerate);
    if (in_obj.take(asset_library_key).toArray().size()) {
        out_messages.emplace_back("Error: assets not supported yet!");
    }

    auto layers = load_layers(in_obj, out_messages);
    comp->set_layers(layers);
    Q_ASSERT(layers.empty());

    for (const auto &element : in_obj.keys()) {
        const static QString msg("Error: Unsupproted element : %1 in composition");
        out_messages.emplace_back(msg.arg(element));
    }
    return comp;
}

} // namespace eao::Lottie
