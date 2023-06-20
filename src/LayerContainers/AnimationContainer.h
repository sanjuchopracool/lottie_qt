#ifndef ANIMATIONCONTAINER_H
#define ANIMATIONCONTAINER_H

#include <memory>

#include <QPixmap>
#include <vector>

#include "TransformedPaintBuffer.h"

class QPainter;

namespace Lottie {
class Animation;

class AnimationContainer
{
public:
    AnimationContainer(const Animation *animation);
    ~AnimationContainer();

    void draw(QPainter* painter);
    bool update(FrameType t, bool force_update);

    void resize(int x, int y);
private:
    void on_resize();
    void load_layers();

private:
    const Animation* m_animation;
    PaintBufferInfo m_buffer_info;
    FrameType m_last_updated_frame = -1;

    // layers
    std::vector<std::unique_ptr<TransformedPaintBuffer>> m_layers;
};
}

#endif // ANIMATIONCONTAINER_H
