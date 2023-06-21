#ifndef ANYVALUECONTAINER_H
#define ANYVALUECONTAINER_H

#include <lottielib.h>
#include <limits>

template <typename T>
class AnyValueContainer
{
public:

    void set_value(const T& value, eao::FrameType frame) {
        m_last_update_frame = frame;
        m_need_update = false;
        m_value = value;
    }

    const T& value() const
    {
        return  m_value;
    }

    void set_needs_update()
    {
        m_need_update = true;
    }

    bool needs_update() const
    {
        return  m_need_update;
    }

protected:
    T m_value;
    bool m_need_update = true;
    eao::FrameType m_last_update_frame = std::numeric_limits<float>::max();
};

#endif // ANYVALUECONTAINER_H
