#ifndef INTERPOLATABLE_H
#define INTERPOLATABLE_H

namespace eao {

template<typename T>
T interpolate(const T& from,const T& to, float amount)
{
    return  from + (to - from) * amount;
}

} // namespace eao

#endif // INTERPOLATABLE_H
