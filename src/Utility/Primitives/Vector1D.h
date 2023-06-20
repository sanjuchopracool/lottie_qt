#ifndef VECTOR1D_H
#define VECTOR1D_H

#include <QJsonArray>
#include <QJsonValue>

namespace Lottie
{
using Vector1D = double;
inline void decode(Vector1D &val, const QJsonValue &in_value)
{
    val =  in_value.isArray() ? in_value.toArray().at(0).toDouble() : in_value.toDouble();
}
}
#endif // VECTOR1D_H
