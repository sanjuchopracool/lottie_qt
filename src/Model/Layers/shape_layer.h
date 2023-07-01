#ifndef SHAPELAYER_H
#define SHAPELAYER_H

#include "layer.h"
#include "model/shape_items/shape_item.h"

#include <QList>

namespace eao {

class ShapeLayer : public Layer
{
public:
    ShapeLayer();
    ~ShapeLayer() override;

    void decode(QJsonObject& in_obj,QList<QString> &out_messages) override;

public:
    std::vector<ShapeItem *> m_shapes;
};
}
#endif // SHAPELAYER_H
