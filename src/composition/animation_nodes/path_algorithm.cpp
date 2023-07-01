#include "path_algorithm.h"

#include <profiler.h>
#include <QDebug>
#include <QPainterPath>

namespace eao {

void cubic_split(std::vector<QPointF> &points, qreal t, bool from_start = true)
{
    //https://www.geogebra.org/m/WPHQ9rUt
    auto p1 = points[0];
    auto p2 = points[1];
    auto p3 = points[2];
    auto p4 = points[3];
    auto p5 = (1 - t) * p1 + t * p2;
    auto p6 = (1 - t) * p2 + t * p3;
    auto p7 = (1 - t) * p3 + t * p4;
    auto p8 = (1 - t) * p5 + t * p6;
    auto p9 = (1 - t) * p6 + t * p7;
    auto bz = (1 - t) * p8 + t * p9;
    if (from_start) {
        points[0] = bz;
        points[1] = p9;
        points[2] = p7;
    } else {
        points[1] = p5;
        points[2] = p8;
        points[3] = bz;
    }
}
void cubic_split(std::vector<QPointF> &points, qreal t1, qreal t2)
{
    cubic_split(points, t1, true);
    t2 = (t2 - t1) / (1 - t1);
    cubic_split(points, t2, false);
}

void trim_path(QPainterPath &path, qreal start, qreal end, qreal offset)
{
    AutoProfiler d("T");
    if (std::abs(end - start) > std::numeric_limits<float>::epsilon()) {
        if (std::abs(end - start - 1) > std::numeric_limits<float>::epsilon()) {
            QPainterPath result;
            qreal total_length = path.length();
            qreal start_length = total_length * start;
            qreal end_length = total_length * end;
            if (start_length > end_length)
                std::swap(start_length, end_length);

            qreal offset_length = offset * total_length;
            start_length += offset_length;
            end_length += offset_length;
            start_length -= static_cast<int>(start_length / total_length) * total_length;
            end_length -= static_cast<int>(end_length / total_length) * total_length;

            bool rotated = false;
            if (start_length > end_length) {
                rotated = true;
            }

            int element_count = path.elementCount();
            std::vector<QPointF> points(4);
            int index = 0;

            qreal length_so_far = 0;
            bool found_start = false;
            bool end_found = false;
            auto check_start_end = [&]() -> bool {
                bool is_start_seg = false;
                bool is_end_seg = false;
                if (index != 0) {
                    auto last_point = points[index];
                    // new qpainterpath

                    if (index == 3) {
                        QPainterPath current_path(points[0]);
                        current_path.cubicTo(points[1], points[2], points[3]);
                        qreal seg_length = current_path.length();
                        qreal length_after_seg = length_so_far + seg_length;
                        if (!found_start && length_so_far <= start_length
                            && start_length <= length_after_seg) {
                            is_start_seg = true;
                        }

                        bool find_end = (!rotated || found_start);
                        if (find_end && length_so_far <= end_length
                            && end_length <= length_after_seg) {
                            is_end_seg = true;
                        }

                        if (is_start_seg) {
                            // both start and end in this segment
                            // start in this segment but not end
                            qreal start_percent = (start_length - length_so_far) / seg_length;
                            found_start = true;
                            if (is_end_seg) {
                                qreal end_percent = (end_length - length_so_far) / seg_length;
                                cubic_split(points, start_percent, end_percent);
                            } else {
                                cubic_split(points, start_percent, true);
                            }
                            result.moveTo(points[0]);
                        } else if (found_start && !is_end_seg) { // already started but not end
                        } else if (is_end_seg) {                 // end found
                            qreal end_percent = (end_length - length_so_far) / seg_length;
                            cubic_split(points, end_percent, false);
                        }
                        if (found_start)
                            result.cubicTo(points[1], points[2], points[3]);
                        length_so_far = length_after_seg;
                    } else if (1 == index) {
                        QPainterPath current_path(points[0]);
                        current_path.lineTo(points[1]);
                        qreal seg_length = current_path.length();
                        qreal length_after_seg = length_so_far + seg_length;
                        if (!found_start && length_so_far <= start_length
                            && start_length <= length_after_seg) {
                            is_start_seg = true;
                        }

                        bool find_end = (!rotated || found_start);
                        if (find_end && length_so_far <= end_length
                            && end_length <= length_after_seg) {
                            is_end_seg = true;
                        }

                        if (is_start_seg) {
                            // both start and end in this segment
                            // start in this segment but not end
                            qreal start_percent = (start_length - length_so_far) / seg_length;
                            points[0] = points[0] + start_percent * (points[1] - points[0]);
                            found_start = true;
                            if (is_end_seg) {
                                qreal end_percent = (end_length - length_so_far) / seg_length;
                                points[1] = points[0] + end_percent * (points[1] - points[0]);
                            }
                            result.moveTo(points[0]);
                        } else if (found_start && !is_end_seg) { // already started but not end
                        } else if (is_end_seg) {                 // end found
                            qreal end_percent = (end_length - length_so_far) / seg_length;
                            points[1] = points[0] + end_percent * (points[1] - points[0]);
                        }
                        if (found_start)
                            result.lineTo(points[1]);
                        length_so_far = length_after_seg;
                    }

                    points[0] = last_point;
                    index = 0;
                }
                return is_end_seg;
            };

            auto evaluate = [&](QPointF p) -> bool {
                bool result = check_start_end();
                points[++index] = p;
                return result;
            };

            bool trimmed = false;
            while (!trimmed) {
                length_so_far = 0;
                for (int i = 0; i < element_count; ++i) {
                    if (trimmed)
                        break;

                    QPainterPath::Element el = path.elementAt(i);
                    switch (el.type) {
                    case QPainterPath::MoveToElement:
                        index = 0;
                        points[index] = el;
                        break;
                    case QPainterPath::LineToElement:
                        trimmed = evaluate(el);
                        break;
                    case QPainterPath::CurveToElement:
                        trimmed = evaluate(el);
                        break;
                    case QPainterPath::CurveToDataElement:
                        points[++index] = el;
                        break;
                    default:
                        break;
                    }
                }
                if (!trimmed)
                    trimmed = check_start_end();
            }
            path = result;
        }
    } else {
        path.clear();
    }
}

} // namespace eao
