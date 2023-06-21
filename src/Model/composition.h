#ifndef EAO_COMPOSITION_H
#define EAO_COMPOSITION_H

#include "../lottielib.h"
#include <QList>

class QJsonObject;

namespace eao {

class LayerModel;
class Composition
{
public:
    Composition();
    ~Composition();

    void decode(QJsonObject &in_obj, QList<QString> &out_messages);

public:
    QString m_version;
    FrameType m_in_point;
    FrameType m_out_point;
    FrameType m_framerate;
    CoordinateSpace m_type;
    int m_width;
    int m_height;

    QList<LayerModel*> m_layers;
};

} // namespace eao

#endif // EAO_COMPOSITION_H
