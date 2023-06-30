#ifndef PATH_NODE_H
#define PATH_NODE_H

#include <QPainterPath>

namespace eao {

class PathNode
{
public:
    const QPainterPath &path() const { return m_path; }
    virtual ~PathNode() {}

protected:
    QPainterPath m_path;
};

} // namespace eao

#endif // PATH_NODE_H
