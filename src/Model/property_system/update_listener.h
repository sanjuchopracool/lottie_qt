#ifndef UPDATE_LISTENER_H
#define UPDATE_LISTENER_H

namespace eao {

class PropertyUpdateListener
{
public:
    virtual ~PropertyUpdateListener() {}
    virtual void on_update() = 0;
};

class SimpleUpdateListener : public PropertyUpdateListener
{
    virtual void on_update() override { m_dirty = true; }

protected:
    bool m_dirty = true;
};

class CascadeUpdateListener : public PropertyUpdateListener
{
public:
    CascadeUpdateListener(PropertyUpdateListener *listener = nullptr)
        : m_listener(listener)
    {}

    virtual void on_update() override
    {
        m_dirty = true;
        if (m_listener)
            m_listener->on_update();
    }

    void set_listener(PropertyUpdateListener *listener) { m_listener = listener; }

protected:
    PropertyUpdateListener *m_listener;
    bool m_dirty = true;
};

} // namespace eao
#endif // UPDATE_LISTENER_H
