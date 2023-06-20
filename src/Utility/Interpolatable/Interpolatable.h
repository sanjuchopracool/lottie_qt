#ifndef INTERPOLATABLE_H
#define INTERPOLATABLE_H

namespace Lottie {

template<typename T>
T interpolate(const T& from,const T& to, float amount)
{
    return  from + (to - from) * amount;
}

}

#endif // INTERPOLATABLE_H
