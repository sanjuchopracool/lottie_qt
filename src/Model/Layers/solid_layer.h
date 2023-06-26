#ifndef SOLIDLAYER_H
#define SOLIDLAYER_H

#include "layer.h"
#include <QList>

namespace eao {

class SolidLayer : public Layer
{
public:
    SolidLayer();
    ~SolidLayer() override;

    int width() const { return m_width; }
    int height() const { return m_height; }
    QColor color() const { return m_color; }

    void decode(QJsonObject &in_obj, QList<QString> &out_messages) override;

private:
    QColor m_color;
    int m_width;
    int m_height;
};
}
#endif // SOLIDLAYER_H
