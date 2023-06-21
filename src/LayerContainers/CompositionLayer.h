#ifndef COMPOSITION_LAYER_H
#define COMPOSITION_LAYER_H

#include "../lottielib.h"

#include <QPixmap>
#include <memory>

namespace eao {
class LayerModel;

struct PaintBufferInfo
{
    PaintBufferInfo(const QSize& size, qreal scale_x, qreal scale_y)
        : m_size(size), m_scale_x(scale_x), m_scale_y(scale_y)
    {

    }

    PaintBufferInfo() {}

    QSize m_size;
    qreal m_scale_x = 1;
    qreal m_scale_y = 1;
};

class PaintBuffer
{
public:
    virtual ~PaintBuffer() {}

    virtual void update_buffer_info(const PaintBufferInfo &info);
    virtual void draw(QPainter* painter, FrameType t) const;
    virtual std::unique_ptr<QPainter> painter(FrameType t);

    void save();

protected:
    PaintBufferInfo m_buffer_info;
    QPixmap m_pixmap;
};

class CompositionLayer : public PaintBuffer
{
public:
    CompositionLayer(const PaintBufferInfo &info);
    virtual ~CompositionLayer() {}

    virtual bool update(FrameType t,bool force_update) = 0;
};
}

#endif // COMPOSITION_LAYER_H
