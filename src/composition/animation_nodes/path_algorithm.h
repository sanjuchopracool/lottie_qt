#ifndef PATH_ALGORITHM_H
#define PATH_ALGORITHM_H

#include <qtypes.h>

class QPainterPath;
namespace eao {

void trim_path(QPainterPath &path, qreal start, qreal end, qreal offset);
}

#endif // PATH_ALGORITHM_H
