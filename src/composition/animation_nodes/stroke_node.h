#ifndef STROKE_NODE_H
#define STROKE_NODE_H

#include "utility/primitives/dash_element.h"
#include "animation_node.h"
#include <model/property_system/property.h>
#include <utility/primitives/utility.h>
#include <composition/interfaces/painting_element.h>

#include <QPen>
#include <memory>

namespace eao {
class Stroke;
class PathNode;

class StrokeNode : public ShapeItemNode, public PaintingElement
{
public:
    StrokeNode(const Stroke &stroke);
    bool update(FrameType t, bool force_update) override;

    //    void render(QPainter *painter) override;
    void set_content(const std::vector<ShapeItemNode *> &,
                     const std::vector<ShapeItemNode *> &items_after) override;

    void draw(QPainter *painter, int parent_alpha) override;

private:
    const Stroke &m_stroke;
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<Vector1D> m_width;
    PropertyAnimatorPtr<QVector4D> m_color;
    std::vector<DashElement> m_dashPattern;
    std::vector<const PathNode *> m_paths;
};
} // namespace eao

#endif // STROKE_NODE_H
