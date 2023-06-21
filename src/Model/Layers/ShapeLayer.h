#ifndef SHAPELAYER_H
#define SHAPELAYER_H

#include "LayerModel.h"
#include "../ShapeItems/ShapeItem.h"

#include <QList>

namespace eao {

class ShapeLayer : public LayerModel
{
public:
    ShapeLayer();
    ~ShapeLayer() override;

    void decode(const QJsonObject& in_obj,QList<QString> &out_messages) override;

public:
    QList<ShapeItem*> m_shapes;
};
}
#endif // SHAPELAYER_H
