#include "solid_layer.h"

#include <QJsonObject>
#include <QJsonArray>

namespace eao {

namespace {
const QStringView color_key = u"sc";
const QStringView width_key = u"sw";
const QStringView height_key = u"sh";
}

SolidLayer::SolidLayer()
{

}

SolidLayer::~SolidLayer()
{
}

void SolidLayer::decode(QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_color = QColor::fromString(in_obj.take(color_key).toString());
    m_width = in_obj.take(width_key).toInt();
    m_height = in_obj.take(height_key).toInt();
    LayerModel::decode(in_obj, out_messages);

    for(const auto& element : in_obj.keys()) {
        const static QString msg("Error: Unsupproted element : %1 in Solid Layer");
        out_messages.emplace_back(msg.arg(element));
    }
}

}
