#ifndef CURVEVERTEX_H
#define CURVEVERTEX_H

#include <QPointF>

namespace Lottie {

class CurveVertex
{
public:
    CurveVertex(const QPointF& point = QPointF(),
                const QPointF& in_point = QPointF(),
                const QPointF& out_point = QPointF())
        : m_point(point),
          m_in_point(in_point),
          m_out_point(out_point)
    {

    }

    static CurveVertex from_relative(const QPointF& point,
                                     const QPointF& in_point,
                                     const QPointF& out_point)
    {
        return CurveVertex(point, point + in_point, point + out_point);
    }

    QPointF in_relative_tangent() const
    {
        return (m_point - m_in_point);
    }

    QPointF out_relative_tangent() const
    {
        return (m_point - m_out_point);
    }

    CurveVertex reveresed() const
    {
        return  CurveVertex(m_point, m_out_point, m_in_point);
    }

    CurveVertex reveresed(const QPointF& translation) const
    {
        return  CurveVertex(m_point + translation, m_in_point + translation, m_out_point + translation);
    }

    qreal distance_to(const CurveVertex& to, int sample = 25) const;

public:
    QPointF m_point;
    QPointF m_in_point;
    QPointF m_out_point;
};

struct SplitResult
{
    CurveVertex start;
    CurveVertex trim_point;
    CurveVertex end;
};

SplitResult split_curve(const CurveVertex &from, const CurveVertex &to, float amount);
SplitResult trim_curve(const CurveVertex &from,
                       const CurveVertex &to,
                       float at_length,
                       float curve_length,
                       int max_samples,
                       float accouracy = 1.0);
}

#endif // CURVEVERTEX_H
