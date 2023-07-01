#ifndef ANIMATIONNODEFACTORY_H
#define ANIMATIONNODEFACTORY_H

#include <memory>
#include <QList>

namespace eao {
class ShapeItemNode;
class PathNode;
class ShapeItem;

namespace AnimationNodeFactory {

std::unique_ptr<ShapeItemNode> node_for_shape_item(const ShapeItem &shape_item);
}
}
#endif // ANIMATIONNODEFACTORY_H
