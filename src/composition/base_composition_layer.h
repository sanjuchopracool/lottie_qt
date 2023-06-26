#ifndef BASE_COMPOSITION_LAYER_H
#define BASE_COMPOSITION_LAYER_H

#include "composition/interfaces/painting_element.h"
#include "lottielib.h"

#include <memory>
#include <QTransform>

namespace eao {

class LayerModel;
class LayerTransformationNode;

class BaseCompositionLayer : public PaintingElement
{
public:
    BaseCompositionLayer(const LayerModel &layer_model);
    ~BaseCompositionLayer() override;

    FrameType local_frame(FrameType t) const;
    void draw(QPainter *painter, int alpha) override;

    virtual void draw_layer(QPainter *painter, int alpha) = 0;
    virtual void update(FrameType t, bool force_update);

    QTransform tranform() const;
    int opacity() const;

private:
    const LayerModel &m_layer_model;
    std::unique_ptr<LayerTransformationNode> m_transformation;
};

} // namespace eao

#endif // BASE_COMPOSITION_LAYER_H
