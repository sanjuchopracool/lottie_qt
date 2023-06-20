#ifndef ANIMATIONNODEFACTORY_H
#define ANIMATIONNODEFACTORY_H

#include <memory>
#include <QList>

namespace Lottie {
class ShapeNodeInterface;
class PathNode;
class ShapeItem;

namespace AnimationNodeFactory {

std::unique_ptr<ShapeNodeInterface> node_for_shape(ShapeItem *shape_item, QList<PathNode *> &paths);

}
}
#endif // ANIMATIONNODEFACTORY_H
