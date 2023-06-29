#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H

#include "lottielib.h"
#include <QList>
#include <QPainterPath>

class QPainter;

namespace eao {

class PathNode
{
public:
    const QPainterPath& path() {
        return m_path;
    }
    void set_path(const QPainterPath &path) { m_path = path; }

protected:
    QPainterPath m_path;
};

class ShapeNodeInterface
{
public:
    virtual ~ShapeNodeInterface() {}
    virtual bool update(FrameType t, bool force_update) = 0;
    inline bool is_static() const { return m_is_static; }

    virtual void render(QPainter *painter) {
        Q_UNUSED(painter)
    }

protected:
    bool m_is_static = false;

};
}

#endif // ANIMATIONNODE_H
