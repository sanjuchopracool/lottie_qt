#ifndef FILLNODE_H
#define FILLNODE_H

#include "ShapeNodeInterface.h"
#include "../../NodeRenderSystem/NodeProperties/NodeProperty.h"
#include "../../Utility/Primitives/Utility.h"

#include <memory>

namespace eao {
class Fill;
class FillNode : public ShapeNodeInterface, public RenderNode
{
public:
    FillNode(const Fill *fill);
    bool need_update(FrameType t) const override;
    bool update(FrameType t, bool force_update) override;

    void render(QPainter *painter) override;

private:
    std::unique_ptr<NodeProperty<Vector1D>> m_opacity;
    std::unique_ptr<NodeProperty<QVector4D>> m_color;
};
}

#endif // FILLNODE_H
