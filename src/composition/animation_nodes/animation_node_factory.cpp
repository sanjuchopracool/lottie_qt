#include "animation_node_factory.h"

#include "model/shape_items/ellipse.h"
#include "model/shape_items/fill.h"
#include "model/shape_items/group.h"
#include "model/shape_items/polystar.h"
#include "model/shape_items/rectangle.h"
#include "model/shape_items/repeater.h"
#include "model/shape_items/shape.h"
#include "model/shape_items/shape_transformation.h"
#include "model/shape_items/stroke.h"
#include "model/shape_items/trim.h"

#include "ellipse_node.h"
#include "fill_node.h"
#include "group_node.h"
#include "polystar_node.h"
#include "rectangle_node.h"
#include "repeater_node.h"
#include "shape_node.h"
#include "shape_transformation_node.h"
#include "stroke_node.h"
#include "trim_node.h"

namespace eao {
namespace AnimationNodeFactory {

std::unique_ptr<ShapeItemNode> node_for_shape_item(const ShapeItem &shape_item)
{
    std::unique_ptr<ShapeItemNode> result;
    switch (shape_item.type()) {
    case ShapeType::Group:
    {
        auto group = std::make_unique<GroupNode>(static_cast<const Group &>(shape_item).m_shapes);
        result = std::move(group);
    }
        break;
    case ShapeType::Shape:
    {
        auto shape = std::make_unique<ShapeNode>(static_cast<const Shape &>(shape_item));
        result = std::move(shape);
    }
        break;
    case ShapeType::Merge:
        break;
    case ShapeType::Transform:
    {
        result = std::make_unique<ShapeTransformationNode>(
            static_cast<const ShapeTransformation &>(shape_item));
    }
        break;
    case ShapeType::Fill:
    {
        auto fill = std::make_unique<FillNode>(static_cast<const Fill &>(shape_item));
        result = std::move(fill);
    }
        break;
    case ShapeType::Stroke:
    {
        auto stroke = std::make_unique<StrokeNode>(static_cast<const Stroke &>(shape_item));
        result = std::move(stroke);
    }
        break;
    case ShapeType::Ellipse:
    {
        auto ellipse = std::make_unique<EllipseNode>(static_cast<const Ellipse &>(shape_item));
        result = std::move(ellipse);
    }
        break;
    case ShapeType::Rectangle:
    {
        auto rect = std::make_unique<RectangleNode>(static_cast<const Rectangle &>(shape_item));
        result = std::move(rect);
    }
    break;
    case ShapeType::Star:
    {
        auto polystar = std::make_unique<PolyStarNode>(static_cast<const PolyStar &>(shape_item));
        result = std::move(polystar);
    }
    break;
    case ShapeType::Trim:
    {
        auto trim = std::make_unique<TrimNode>(static_cast<const Trim &>(shape_item));
        result = std::move(trim);
    }
        break;
    case ShapeType::Repeater:
    {
        auto repeater = std::make_unique<RepeaterNode>(static_cast<const Repeater &>(shape_item));
        result = std::move(repeater);
    }
    break;
    default:
        assert(false);
        break;
    }

    return result;
}

}
}
