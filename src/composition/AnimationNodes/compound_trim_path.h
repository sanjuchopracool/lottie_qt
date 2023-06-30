#ifndef COMPOUNDTRIMPATH_H
#define COMPOUNDTRIMPATH_H

#include <vector>

class QPainterPath;

namespace eao {

class TrimNode;
class CompoundTrimPath
{
public:
    CompoundTrimPath();
    ~CompoundTrimPath();
    void add_trim_path(const TrimNode *trim);

    void apply_trim(QPainterPath &path);

private:
    std::vector<const TrimNode *> m_trims;
};

} // namespace eao

#endif // COMPOUNDTRIMPATH_H
