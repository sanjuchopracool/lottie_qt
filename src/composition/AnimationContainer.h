#ifndef ANIMATIONCONTAINER_H
#define ANIMATIONCONTAINER_H

#include <memory>

#include <QPixmap>
#include <vector>

#include "base_composition_layer.h"

class QPainter;

namespace eao {
class Composition;

class AnimationContainer
{
public:
    AnimationContainer(const Composition *animation);
    ~AnimationContainer();

    void draw(QPainter* painter);
    bool update(FrameType t, bool force_update);

    void resize(int x, int y);
private:
    void on_resize();
    void load_layers();

private:
    const Composition* m_animation;
    FrameType m_last_updated_frame = -1;

    // layers
    std::vector<std::unique_ptr<BaseCompositionLayer>> m_layers;

    // scaling information to fit into rendering canvas (painter)
    QSize m_size;
    qreal m_scale_x;
    qreal m_scale_y;

    // if need rendering again
    bool m_dirty = true;
};
}

#endif // ANIMATIONCONTAINER_H
