#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "../../Utility/Interpolatable/Interpolatable.h"
#include "../../Utility/Primitives/Utility.h"
#include "../../lottielib.h"

#include <QVector2D>
#include <QVector3D>
#include <QEasingCurve>

namespace Lottie {

template<typename T>
class KeyFrame
{
public:
    KeyFrame(const T& value,
             const QVector3D& in_sp_tangent = QVector3D(),
             const QVector3D& out_sp_tangent= QVector3D())
        : m_value(value),
          m_time(0),
          m_is_hold(true),
          m_spatial_in_tangent(in_sp_tangent),
          m_spatial_out_tangent(out_sp_tangent)
    {

    }

    KeyFrame(const T& value,
             FrameType time,
             bool is_hold,
             const QVector2D& in_tangent,
             const QVector2D& out_tangent,
             const QVector3D& in_sp_tangent = QVector3D(),
             const QVector3D& out_sp_tangent= QVector3D())
        : m_value(value),
          m_time(time),
          m_is_hold(is_hold),
          m_in_tangent(in_tangent),
          m_out_tangent(out_tangent),
          m_spatial_in_tangent(in_sp_tangent),
          m_spatial_out_tangent(out_sp_tangent)
    {

    }


    T m_value;
    FrameType m_time;
    bool m_is_hold;
    QVector2D m_in_tangent;
    QVector2D m_out_tangent;
    QVector3D m_spatial_in_tangent;
    QVector3D m_spatial_out_tangent;

    double interpolated_progress(const KeyFrame& to, FrameType time) const
    {
        if (time < m_time)
            return 0.0;

        if (to.m_time < time)
            return 1;

        if (m_is_hold)
            return 0.0;


        double progress = remap<FrameType>(time, m_time, to.m_time, 0, 1);
        if ((not m_out_tangent.isNull()) or (not m_in_tangent.isNull()))
        {
            QVector2D out_point = m_out_tangent;
            if (out_point.isNull())
            {
                out_point.setX(0);
                out_point.setY(0);
            }

            QVector2D in_point = to.m_in_tangent;
            if (in_point.isNull())
            {
                in_point.setX(1);
                in_point.setY(1);
            }

            QEasingCurve easingCurve(QEasingCurve::BezierSpline);
            easingCurve.addCubicBezierSegment(out_point.toPointF(), in_point.toPointF(), QPointF(1, 1));
            progress = easingCurve.valueForProgress(progress);
        }

        return progress;
    }

    T interpolate_to(const KeyFrame& to, double progress) const {
        return interpolate<T>(m_value, to.m_value, progress);
    }
};

}

#endif // KEYFRAME_H
