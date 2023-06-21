#ifndef SINGLEVALUEPROVIDER_H
#define SINGLEVALUEPROVIDER_H

#include "../AnyValueProvider.h"

namespace eao {
template <typename T>
class SingleValueProvider : public AnyValueProvider<T>
{
public:
    using valueType = T;

    SingleValueProvider(const valueType& val)
        : m_value(val)
    {
    }

    bool has_update(eao::FrameType) override
    {
        return m_has_update;
    }

    const valueType& value(eao::FrameType) override
    {
        m_has_update = false;
        return m_value;
    }

    void set_value(const valueType& val)
    {
        m_value = val;
        m_has_update = true;
    }

    bool is_static() const { return true;}
private:
    mutable bool m_has_update = true;
    T m_value;
};
}
#endif // SINGLEVALUEPROVIDER_H
