#include "solid_composition_layer.h"

#include "Model/Layers/solid_layer.h"
#include <QPainter>
#include <QDebug>

namespace  eao {
SolidCompositionLayer::SolidCompositionLayer(const SolidLayer &solid_layer)
    : BaseCompositionLayer(solid_layer)
    , m_solid_layer(solid_layer)
{}

void SolidCompositionLayer::draw_layer(QPainter *painter, int alpha)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_solid_layer.m_color);
    painter->drawRect(0, 0, m_solid_layer.m_width, m_solid_layer.m_height);
}

} // namespace eao
