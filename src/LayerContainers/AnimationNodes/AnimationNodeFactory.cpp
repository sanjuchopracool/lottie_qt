#include "AnimationNodeFactory.h"

#include "../../Model/ShapeItems/Group.h"
#include "../../Model/ShapeItems/Shape.h"
#include "../../Model/ShapeItems/Ellipse.h"
#include "../../Model/ShapeItems/rectangle.h"
#include "../../Model/ShapeItems/Fill.h"
#include "../../Model/ShapeItems/Stroke.h"
#include "../../Model/ShapeItems/Trim.h"
#include "../../Model/ShapeItems/ShapeTransformation.h"

#include "GroupNode.h"
#include "ShapeNode.h"
#include "FillNode.h"
#include "StrokeNode.h"
#include "EllipseNode.h"
#include "TrimNode.h"
#include "ShapeTransformationNode.h"
#include "rectangle_node.h"

namespace eao {
namespace AnimationNodeFactory {

std::unique_ptr<ShapeNodeInterface> node_for_shape(ShapeItem *shape_item, QList<PathNode*>& paths)
{
    std::unique_ptr<ShapeNodeInterface> result;
    switch (shape_item->m_type) {
    case ShapeType::Group:
    {
        auto group =  std::make_unique<GroupNode>(static_cast<Group*>(shape_item));
        paths.append(group->group_paths());
        result = std::move(group);
    }
        break;
    case ShapeType::Shape:
    {
        auto shape = std::make_unique<ShapeNode>(static_cast<Shape*>(shape_item));
        paths.append(shape.get());
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
        fill->setPaths(paths);
        result = std::move(fill);
    }
        break;
    case ShapeType::Stroke:
    {
        auto stroke = std::make_unique<StrokeNode>(static_cast<Stroke*>(shape_item));
        stroke->setPaths(paths);
        result = std::move(stroke);
    }
        break;
    case ShapeType::Ellipse:
    {
        auto ellipse = std::make_unique<EllipseNode>(static_cast<Ellipse*>(shape_item));
        paths.append(ellipse.get());
        result = std::move(ellipse);
    }
        break;
    case ShapeType::Rectangle:
    {
        auto rect = std::make_unique<RectangleNode>(static_cast<Rectangle*>(shape_item));
        paths.append(rect.get());
        result = std::move(rect);
    }
    break;
    case ShapeType::Trim:
    {
        auto trim = std::make_unique<TrimNode>(static_cast<Trim*>(shape_item));
        trim->setPaths(paths);
        result = std::move(trim);
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
