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

void SolidLayer::decode(const QJsonObject &in_obj, QList<QString> &out_messages)
{
    m_color = QColor::fromString(in_obj.value(color_key).toString());
    m_width = in_obj.value(width_key).toDouble();
    m_height = in_obj.value(height_key).toDouble();
    LayerModel::decode(in_obj, out_messages);
}

}
