#ifndef SHAPELAYER_H
#define SHAPELAYER_H

#include "Model/ShapeItems/ShapeItem.h"
#include "layer.h"

#include <QList>

namespace eao {

class ShapeLayer : public Layer
{
public:
    ShapeLayer();
    ~ShapeLayer() override;

    void decode(QJsonObject& in_obj,QList<QString> &out_messages) override;

public:
    QList<ShapeItem*> m_shapes;
};
}
#endif // SHAPELAYER_H
