#ifndef BASE_COMPOSITION_LAYER_H
#define BASE_COMPOSITION_LAYER_H

#include "composition/interfaces/painting_element.h"
#include "lottielib.h"
#include <Model/property_system/update_listener.h>

#include <memory>
#include <QTransform>

namespace eao {

class Layer;
class LayerTransformationNode;

class BaseCompositionLayer : virtual public PaintingElement, virtual public CascadeUpdateListener
{
public:
    BaseCompositionLayer(const Layer &layer_model);
    ~BaseCompositionLayer() override;

    FrameType local_frame(FrameType t) const;
    void draw(QPainter *painter, int alpha) override;

    virtual void draw_layer(QPainter *painter, int parent_alpha) = 0;
    virtual void update_layer(FrameType t, bool force_update);

    QTransform transform() const;
    int opacity() const;

private:
    const Layer &m_layer_model;
    std::unique_ptr<LayerTransformationNode> m_transformation;
};

} // namespace eao

#endif // BASE_COMPOSITION_LAYER_H
