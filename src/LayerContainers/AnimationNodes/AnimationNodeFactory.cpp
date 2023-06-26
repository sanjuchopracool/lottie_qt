#include "AnimationNodeFactory.h"

#include "Model/ShapeItems/Ellipse.h"
#include "Model/ShapeItems/Fill.h"
#include "Model/ShapeItems/Group.h"
#include "Model/ShapeItems/Shape.h"
#include "Model/ShapeItems/ShapeTransformation.h"
#include "Model/ShapeItems/Stroke.h"
#include "Model/ShapeItems/Trim.h"
#include "Model/ShapeItems/polystar.h"
#include "Model/ShapeItems/rectangle.h"
#include "Model/ShapeItems/repeater.h"

#include "GroupNode.h"
#include "ShapeNode.h"
#include "FillNode.h"
#include "StrokeNode.h"
#include "EllipseNode.h"
#include "TrimNode.h"
#include "ShapeTransformationNode.h"
#include "rectangle_node.h"
#include "polystar_node.h"
#include "repeater_node.h"

namespace eao {
namespace AnimationNodeFactory {

std::unique_ptr<ShapeNodeInterface> node_for_shape(ShapeItem *shape_item)
{
    std::unique_ptr<ShapeNodeInterface> result;
    switch (shape_item->m_type) {
    case ShapeType::Group:
    {
        auto group =  std::make_unique<GroupNode>(static_cast<Group*>(shape_item));
        result = std::move(group);
    }
        break;
    case ShapeType::Shape:
    {
        auto shape = std::make_unique<ShapeNode>(static_cast<Shape*>(shape_item));
        result = std::move(shape);
    }
        break;
    case ShapeType::Merge:
        break;
    case ShapeType::Transform:
    {
        result = std::make_unique<ShapeTransformationNode>(static_cast<ShapeTransformation*>(shape_item));
    }
        break;
    case ShapeType::Fill:
    {
        auto fill = std::make_unique<FillNode>(static_cast<Fill*>(shape_item));
        result = std::move(fill);
    }
        break;
    case ShapeType::Stroke:
    {
        auto stroke = std::make_unique<StrokeNode>(static_cast<Stroke*>(shape_item));
        result = std::move(stroke);
    }
        break;
    case ShapeType::Ellipse:
    {
        auto ellipse = std::make_unique<EllipseNode>(static_cast<Ellipse*>(shape_item));
        result = std::move(ellipse);
    }
        break;
    case ShapeType::Rectangle:
    {
        auto rect = std::make_unique<RectangleNode>(static_cast<Rectangle*>(shape_item));
        result = std::move(rect);
    }
    break;
    case ShapeType::Star:
    {
        auto polystar = std::make_unique<PolyStarNode>(static_cast<PolyStar*>(shape_item));
        result = std::move(polystar);
    }
    break;
    case ShapeType::Trim:
    {
        auto trim = std::make_unique<TrimNode>(static_cast<Trim*>(shape_item));
        result = std::move(trim);
    }
        break;
    case ShapeType::Repeater:
    {
        auto repeater = std::make_unique<RepeaterNode>(static_cast<Repeater*>(shape_item));
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
