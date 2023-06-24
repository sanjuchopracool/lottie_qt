#ifndef TRANSFORMEDPAINTBUFFER_H
#define TRANSFORMEDPAINTBUFFER_H

#include "CompositionLayer.h"

namespace eao {
class LayerModel;
class Transformation3D;
class TransformationNode3D;

class TransformedPaintBuffer : public CompositionLayer
{
public:
    TransformedPaintBuffer(const Transformation3D &transformation, const PaintBufferInfo &info,
                           const LayerModel* model);
    ~TransformedPaintBuffer();

    bool is_static() const { return m_is_static; }
    void draw(QPainter* painter, FrameType t) const override;
    bool update(FrameType t,bool force_update) override;
    
    const TransformationNode3D* transform() { return m_transformation.get();}
    void set_parent_transform(const TransformationNode3D* parent_transform);

    FrameType local_frame(FrameType t) const;
protected:
    bool m_is_static = false;
    const LayerModel *m_layer_model;

    virtual bool need_update(FrameType t) const;
    std::unique_ptr<QPainter> painter(FrameType t) override;
    std::unique_ptr<TransformationNode3D> m_transformation;
};

}

#endif // TRANSFORMEDPAINTBUFFER_H
