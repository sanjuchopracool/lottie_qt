#include "solid_composition_layer.h"

#include "model/layers/solid_layer.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
SolidCompositionLayer::SolidCompositionLayer(const SolidLayer &solid_layer)
    : BaseCompositionLayer(solid_layer)
    , m_layer(solid_layer)
{}

void SolidCompositionLayer::draw_layer(QPainter *painter, int parent_alpha)
{
    QColor color(m_layer.color());

    if (color.alpha() == 0 || opacity() == 0)
        return;

    painter->setPen(Qt::NoPen);
    int alpha = (parent_alpha * color.alpha() * opacity()) / (255 * 100);
    color.setAlpha(alpha);
    painter->setBrush(color);
    painter->drawRect(0, 0, m_layer.width(), m_layer.height());
}

} // namespace eao
