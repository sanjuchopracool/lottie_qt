#ifndef STROKENODE_H
#define STROKENODE_H

#include "NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "ShapeNodeInterface.h"
#include "Utility/Primitives/DashElement.h"

#include <QPen>
#include <memory>

namespace eao {
class Stroke;

class StrokeNode : public ShapeNodeInterface
{
public:
    StrokeNode(const Stroke* stroke);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;
private:
    std::unique_ptr<NodeProperty<Vector1D>> m_opacity;
    std::unique_ptr<NodeProperty<Vector1D>> m_width;
    std::unique_ptr<NodeProperty<QVector4D>> m_color;
    std::vector<DashElement> m_dashPattern;
    QPen m_pen;
};

}

#endif // STROKENODE_H
