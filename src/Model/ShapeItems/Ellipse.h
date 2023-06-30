#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "ShapeItem.h"
#include <Model/property_system/property.h>

#include <QVector2D>

namespace eao {

class Ellipse : public ShapeItem
{
public:
    Ellipse();

    virtual void decode(QJsonObject &in_obj, QList<QString> &out_messages) override;

    const auto &size() const { return m_size; }
    const auto &position() const { return m_position; }
    const auto &direction() const { return m_direction; }

public:
    PropertyPtr<QVector2D> m_size;
    PropertyPtr<QVector2D> m_position;
    PathDirection m_direction;
};
}

#endif // ELLIPSE_H
