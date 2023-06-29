#ifndef FILLNODE_H
#define FILLNODE_H

#include "ShapeNodeInterface.h"
#include "Utility/Primitives/Utility.h"
#include <Model/property_system/property.h>

#include <memory>

namespace eao {
class Fill;
class FillNode : public ShapeNodeInterface, public CascadeUpdateListener
{
public:
    FillNode(const Fill &fill);
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;

private:
    PropertyAnimatorPtr<Vector1D> m_opacity;
    PropertyAnimatorPtr<QVector4D> m_color;
};
}

#endif // FILLNODE_H
