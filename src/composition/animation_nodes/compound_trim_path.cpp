#include "compound_trim_path.h"
#include "path_algorithm.h"
#include "trim_node.h"
namespace eao {

CompoundTrimPath::CompoundTrimPath() {}

CompoundTrimPath::~CompoundTrimPath() {}

void CompoundTrimPath::add_trim_path(const TrimNode *trim)
{
    if (trim)
        m_trims.emplace_back(trim);
}

void CompoundTrimPath::apply_trim(QPainterPath &path)
{
    qreal start = 1;
    qreal end = 1;
    qreal offset = 1.0;

    // TODO assuming simultaneous trim
    for (const TrimNode *trim : m_trims) {
        start *= trim->start() / 100.0f;
        end *= trim->end() / 100.0f;
        offset *= trim->offset() / 360.f;
    }

    trim_path(path, start, end, offset);
}

} // namespace eao
