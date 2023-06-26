#include "NullCompositionLayer.h"

namespace eao {

NullCompositionLayer::NullCompositionLayer(const LayerModel &layer)
    : BaseCompositionLayer(layer)
{
}

void NullCompositionLayer::draw_layer(QPainter *painter, int alpha) {}

} // namespace eao
