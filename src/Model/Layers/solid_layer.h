#ifndef SOLIDLAYER_H
#define SOLIDLAYER_H

#include "LayerModel.h"
#include <QList>

namespace eao {

class SolidLayer : public LayerModel
{
public:
    SolidLayer();
    ~SolidLayer() override;

    void decode(QJsonObject& in_obj,QList<QString> &out_messages) override;

public:
    QColor m_color;
    float m_width;
    float m_height;
};
}
#endif // SOLIDLAYER_H
