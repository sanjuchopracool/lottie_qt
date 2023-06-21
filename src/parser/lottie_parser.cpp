#include "lottie_parser.h"
#include "../Model/composition.h"

#include <QList>
#include <QStringView>

namespace eao::Lottie {

const QList<QStringView> composition_required_fields{u"w", u"h", u"fr", u"layers", u"op", u"ip"};

//const QStringView version_key(u"v");
//const QStringView type_key(u"ddd");
//const QStringView in_point_key(u"ip");
//const QStringView out_point_key(u"op");
//const QStringView framerate_key(u"fr");
//const QStringView width_key(u"w");
//const QStringView height_key(u"h");
//const QStringView layers_key(u"layers");
//const QStringView glyphs_key(u"chars");
//const QStringView fonts_key(u"fonts");
//const QStringView asset_library_key(u"assets");
//const QStringView markers_key(u"markers");

std::unique_ptr<Composition> LottieParser::parse(const QJsonObject &in_obj,
                                                 QStringList &out_messages)
{
    return nullptr;
}

} // namespace eao::Lottie
