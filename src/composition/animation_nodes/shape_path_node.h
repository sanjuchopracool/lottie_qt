#ifndef SHAPE_PATH_NODE_H
#define SHAPE_PATH_NODE_H

#include "animation_node.h"
#include "path_node.h"
#include <memory>

namespace eao {
class CompoundTrimPath;

class ShapePathNode : public PathNode, public ShapeItemNode
{
public:
    ShapePathNode();
    ~ShapePathNode() override;

protected:
    void set_content(const std::vector<ShapeItemNode *> &items_before,
                     const std::vector<ShapeItemNode *> &items_after) override;
    void apply_trim();
    std::unique_ptr<CompoundTrimPath> m_compount_trim;
};

} // namespace eao

#endif // SHAPE_PATH_NODE_H
