#ifndef ELLIPSENODE_H
#define ELLIPSENODE_H

#include <utility/primitives/utility.h>
#include "animation_node.h"
#include "shape_path_node.h"
#include <model/property_system/property.h>
#include <memory>

namespace eao {
class Ellipse;

class EllipseNode : public ShapePathNode
{
public:
    EllipseNode(const Ellipse &ellipse);
    bool update(FrameType t, bool force_update) override;

private:
    void create_path();

private:
    const Ellipse &m_ellipse;
    PropertyAnimatorPtr<QVector2D> m_size;
    PropertyAnimatorPtr<QVector2D> m_position;
};
}

#endif // ELLIPSENODE_H
