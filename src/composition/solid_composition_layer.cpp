#include "solid_composition_layer.h"

#include "Model/Layers/solid_layer.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
SolidCompositionLayer::SolidCompositionLayer(const SolidLayer &solid_layer)
    : BaseCompositionLayer(solid_layer)
    , m_layer(solid_layer)
{}

void SolidCompositionLayer::draw_layer(QPainter *painter, int alpha)
{
    painter->setPen(Qt::NoPen);
    QColor color(m_layer.color());
    alpha = opacity();
    if (alpha < 100) {
        alpha = (alpha * 255) / 100;
        color.setAlpha(alpha);
    }
    qDebug() << color;
    painter->setBrush(color);
    painter->drawRect(0, 0, m_layer.width(), m_layer.height());
}

} // namespace eao
