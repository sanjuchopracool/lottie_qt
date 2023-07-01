#include "null_composition_layer.h"

namespace eao {

NullCompositionLayer::NullCompositionLayer(const Layer &layer)
    : BaseCompositionLayer(layer)
{
}

void NullCompositionLayer::draw_layer(QPainter *painter, int alpha) {}

} // namespace eao
