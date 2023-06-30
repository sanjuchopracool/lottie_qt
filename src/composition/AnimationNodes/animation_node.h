#ifndef ANIMATION_NODE_H
#define ANIMATION_NODE_H

#include "lottielib.h"
#include <Model/property_system/update_listener.h>
#include <QList>
#include <QPainterPath>

class QPainter;

namespace eao {

class PathNode
{
public:
    const QPainterPath &path() const { return m_path; }

protected:
    QPainterPath m_path;
};

class ShapeItemNode : virtual public CascadeUpdateListener
{
public:
    virtual ~ShapeItemNode() {}
    virtual bool update(FrameType t, bool force_update) = 0;
    inline bool is_static() const { return m_is_static; }

    //
    virtual void set_content(const std::vector<ShapeItemNode *> &items_before,
                             const std::vector<ShapeItemNode *> &items_after)
    {}

protected:
    bool m_is_static = false;
};
}

#endif // ANIMATION_NODE_H
