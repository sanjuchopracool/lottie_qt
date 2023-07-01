#include "shape_path_node.h"
#include "compound_trim_path.h"
#include "trim_node.h"

namespace eao {

ShapePathNode::ShapePathNode() {}

ShapePathNode::~ShapePathNode() {}

void ShapePathNode::set_content(const std::vector<ShapeItemNode *> &items_before,
                                const std::vector<ShapeItemNode *> &items_after)
{
    for (ShapeItemNode *item : items_before) {
        TrimNode *trim = dynamic_cast<TrimNode *>(item);
        if (trim && trim->trim_type() == Trim::TrimType::Simultaneously) {
            if (!m_compount_trim) {
                m_compount_trim = std::make_unique<CompoundTrimPath>();
            }
            trim->add_listener(this);
            m_compount_trim->add_trim_path(trim);
        }
    }
}

void ShapePathNode::apply_trim()
{
    if (m_compount_trim) {
        m_compount_trim->apply_trim(m_path);
    }
}

} // namespace eao
