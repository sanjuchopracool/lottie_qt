#ifndef ELLIPSENODE_H
#define ELLIPSENODE_H

#include "Utility/Primitives/Utility.h"
#include "animation_node.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Ellipse;

class EllipseNode : public ShapeItemNode, public PathNode
{
public:
    EllipseNode(const Ellipse &ellipse);
    bool update(FrameType t, bool force_update) override;

private:
    PropertyAnimatorPtr<QVector2D> m_size;
    PropertyAnimatorPtr<QVector2D> m_position;
};
}

#endif // ELLIPSENODE_H
