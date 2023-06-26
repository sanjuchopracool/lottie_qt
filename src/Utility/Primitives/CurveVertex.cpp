#include "CurveVertex.h"
#include "Utility.h"
#include "Utility/Interpolatable/Interpolatable.h"

namespace eao {

SplitResult split_curve(const CurveVertex& from, const CurveVertex& to, float amount)
{
    SplitResult result;
    if (amount <= 0)
    {
        result.start = CurveVertex::from_relative(from.m_point, from.in_relative_tangent(), QPointF());
        result.trim_point = CurveVertex::from_relative(from.m_point, QPointF(), from.out_relative_tangent());
        result.end = to;
        return  result;
    }

    if (amount>=1)
    {
        result.start = from;
        result.trim_point = CurveVertex::from_relative(to.m_point, to.in_relative_tangent(), QPointF());
        result.end = CurveVertex::from_relative(to.m_point, QPointF(), to.out_relative_tangent());
        return  result;
    }

    if (from.out_relative_tangent().isNull() and to.in_relative_tangent().isNull())
    {
        result.start = from;
        result.trim_point = CurveVertex(interpolate<QPointF>(from.m_point, to.m_point, amount));
        result.end = to;
    }

    QPointF a = interpolate<QPointF>(from.m_point, from.m_out_point, amount);
    QPointF b = interpolate(from.m_out_point, to.m_in_point, amount);
    auto c = interpolate(to.m_in_point, to.m_point, amount);
    auto d = interpolate(a, b, amount);
    auto e = interpolate(b, c, amount);
    auto f = interpolate(d, e, amount);
    result.start = CurveVertex(from.m_point, from.m_in_point, a);
    result.trim_point = CurveVertex(f, d, e);
    result.end = CurveVertex(to.m_point, c, to.m_out_point);
    return result;
}

SplitResult trim_curve(const CurveVertex& from, const CurveVertex& to,
                        float at_length, float curve_length,
                        int max_samples, float accouracy)
{
    auto current_position = at_length/curve_length;
    auto results = split_curve(from, to, current_position);

    if (max_samples == 0)
        return  results;

    for(int i = 0; i < max_samples; ++i)
    {
        auto length = results.start.distance_to(results.trim_point);
        const auto length_diff = at_length - length;

        if (length_diff < accouracy)
            return  results;

        const auto diff_position = qMax( qMin((current_position/length)*length_diff, current_position*0.5), current_position* -0.5);
        current_position = diff_position + current_position;
        results = split_curve(from, to, current_position);
    }

    return  results;
}


qreal CurveVertex::distance_to(const CurveVertex &to, int sample) const
{
    Q_UNUSED(sample)
    if (this->out_relative_tangent().isNull() and to.in_relative_tangent().isNull())
        return distance_between(m_point, to.m_point);

//    qreal distance = 0;
//    QPointF previous_point = m_point;
//    for(int i =0; i < sample; ++i)
//    {
//        auto next_point = split_curve(*this, to, static_cast<float>(i)/static_cast<float>(sample)).trim_point.m_point;
//        distance += distance_between(previous_point, next_point);
//        previous_point = next_point;
//    }

//    distance += distance_between(previous_point, to.m_point);
//    return  distance;

    QPainterPath path(m_point);
    path.cubicTo(m_out_point, to.m_in_point, to.m_point);
    return path.length();
}

}
