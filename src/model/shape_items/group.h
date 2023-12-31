#ifndef GROUP_H
#define GROUP_H

#include "shape_item.h"
#include <vector>

namespace eao {

class Group : public ShapeItem
{
public:
    Group();
    ~Group() override;

    virtual void decode(QJsonObject& in_obj, QList<QString> &out_messages) override;

public:
    std::vector<ShapeItem *> m_shapes;
};
}
#endif // GROUP_H
