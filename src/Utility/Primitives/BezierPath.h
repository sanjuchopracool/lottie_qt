#ifndef BEZIERPATH_H
#define BEZIERPATH_H

#include "PathElement.h"

#include <QList>
#include <QJsonObject>
#include <QPainterPath>
#include "../Interpolatable/Interpolatable.h"
#include "../../AutoProfiler.h"

namespace Lottie {

class BezierPath
{
public:
    BezierPath() = default;
    ~BezierPath();
    BezierPath(const CurveVertex& vertex);

    void move_to_start_point(const CurveVertex& vertex);
    void add_vertex(const CurveVertex& vertex);
    void close();
    void add_element(const PathElement& element);

    void decode(const QJsonValue& in_value);
    const QPainterPath& path() const;
public:
    QList<PathElement> m_elements;
    bool m_closed = false;
    double m_length = 0.0;

    // calculated
    mutable QPainterPath m_path;
};

template<>
inline CurveVertex interpolate<CurveVertex>(const CurveVertex &from, const CurveVertex &to, float amount)
{
     return CurveVertex(interpolate<QPointF>(from.m_point, to.m_point, amount),
                        interpolate<QPointF>(from.m_in_point, to.m_in_point, amount),
                        interpolate<QPointF>(from.m_out_point, to.m_out_point, amount));
}

template<>
inline BezierPath interpolate<BezierPath>(const BezierPath &from, const BezierPath &to, float amount)
{
    BezierPath result;
    {
        AutoProfiler p("P");
        int min_count = qMin(from.m_elements.count(), to.m_elements.count());
        for(int i = 0; i < min_count; ++i )
        {
            auto p1 = from.m_elements[i].m_vertex;
            auto p2 = to.m_elements[i].m_vertex;

            result.add_vertex(interpolate(p1, p2, amount));
        }
    }
    return result;
}
}
#endif // BEZIERPATH_H
