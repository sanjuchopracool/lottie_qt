#ifndef UPDATE_LISTENER_H
#define UPDATE_LISTENER_H

#include "property_update_listener.h"
#include <set>

namespace eao {

class SimpleUpdateListener : public PropertyUpdateListener
{
    virtual void on_update() override { m_dirty = true; }

protected:
    bool m_dirty = true;
};

class CascadeUpdateListener : public PropertyUpdateListener
{
public:
    CascadeUpdateListener(PropertyUpdateListener *listener = nullptr) { add_listener(listener); }

    virtual void on_update() override
    {
        m_dirty = true;
        for (auto &listener : m_listeners)
            listener->on_update();
    }

    void add_listener(PropertyUpdateListener *listener)
    {
        if (listener)
            m_listeners.emplace(listener);
    }

protected:
    std::set<PropertyUpdateListener *> m_listeners;
    bool m_dirty = true;
};

} // namespace eao
#endif // UPDATE_LISTENER_H
