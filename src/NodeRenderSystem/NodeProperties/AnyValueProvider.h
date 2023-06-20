#ifndef ANYVALUEPROVIDER_H
#define ANYVALUEPROVIDER_H

#include <lottielib.h>

template <typename T>
class AnyValueProvider
{
public:
    using valueType = T;
    virtual bool has_update(Lottie::FrameType frame) const = 0;
    virtual const valueType& value(Lottie::FrameType frame) = 0;

    virtual ~AnyValueProvider() {}
    virtual bool is_static() const { return false;}
};

#endif // ANYVALUEPROVIDER_H
