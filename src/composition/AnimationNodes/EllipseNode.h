#ifndef ELLIPSENODE_H
#define ELLIPSENODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Ellipse;

class EllipseNode : public ShapeNodeInterface, public PathNode, public SimpleUpdateListener
{
public:
    EllipseNode(const Ellipse &ellipse);
    bool update(FrameType t, bool force_update) override;

private:
    PropertyAnimatorPtr<QVector2D> m_size;
    PropertyAnimatorPtr<QVector2D> m_position;
    QPainterPath m_ellipse_path;
};
}

#endif // ELLIPSENODE_H
