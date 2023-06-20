#ifndef ANIMATION_H
#define ANIMATION_H

#include "../lottielib.h"
#include "Layers/LayerModel.h"
#include <QJsonObject>
#include <QList>

namespace Lottie {
class Animation
{
public:
    Animation();
    ~Animation();

    void decode(const QJsonObject& in_obj);

public:
    QString m_version;
    FrameType m_start_frame;
    FrameType m_end_frame;
    FrameType m_frame_rate;
    CoordinateSpace m_type;
    int m_width;
    int m_height;

    QList<LayerModel*> m_layers;
};

}

#endif // ANIMATION_H
