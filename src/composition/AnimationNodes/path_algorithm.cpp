#include "path_algorithm.h"

#include <AutoProfiler.h>
#include <QDebug>
#include <QPainterPath>

namespace eao {

void trim_path(QPainterPath &path, qreal start, qreal end, qreal offset)
{
    start /= 100;
    end /= 100;
    offset /= 100;

    if (std::abs(end - start) > std::numeric_limits<float>::epsilon()) {
        if (std::abs(end - start - 1) > std::numeric_limits<float>::epsilon()) {
            qreal gap = (end - start) / 100.0;
            AutoProfiler p("T");
            QPainterPath new_path;
            new_path.moveTo(path.pointAtPercent(start));
            qDebug() << "path length: " << path.length();
            for (qreal trim = start + gap; trim <= end; trim += gap) {
                new_path.lineTo(path.pointAtPercent(trim));
            }
            //            qDebug() << start << end << path.length() << new_path.length();
            path = new_path;
        }
    } else {
        path.clear();
    }
}

} // namespace eao
