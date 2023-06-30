#include "compount_trim_path.h"
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
    qreal start = 0.01f;
    qreal end = 0.01f;
    qreal offset = 1.0 / 360.f;

    // TODO assuming simultaneous trim
    for (const TrimNode *trim : m_trims) {
        start *= trim->start();
        end *= trim->end();
        offset *= trim->offset();
    }

    trim_path(path, start, end, offset);
}

} // namespace eao
