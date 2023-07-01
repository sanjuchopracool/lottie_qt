#ifndef PROPERTY_UPDATE_LISTENER_H
#define PROPERTY_UPDATE_LISTENER_H

namespace eao {

class PropertyUpdateListener
{
public:
    virtual ~PropertyUpdateListener() {}
    virtual void on_update() = 0;
};

} // namespace eao
#endif // PROPERTY_UPDATE_LISTENER_H
