#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Model/Keyframes/KeyFrameGroup.h"
#include "ShapeItem.h"

namespace eao {

class Ellipse : public ShapeItem
{
public:
    Ellipse();

    virtual void decode(QJsonObject& in_obj, QList<QString>& out_messages) override;

public:
    KeyFrameGroup<QVector2D> m_size;
    KeyFrameGroup<QVector2D> m_position;
    PathDirection m_direction;
};
}

#endif // ELLIPSE_H
