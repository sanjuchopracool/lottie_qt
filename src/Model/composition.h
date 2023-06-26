#ifndef EAO_COMPOSITION_H
#define EAO_COMPOSITION_H

#include "Layers/layer.h"
#include "lottielib.h"
#include <memory>
#include <vector>

namespace eao {

class Composition
{
public:
    using LayerPtr = std::unique_ptr<Layer>;
    using LayerList = std::vector<LayerPtr>;

    Composition(QString name,
                QString version,
                int width,
                int height,
                FrameType in_point,
                FrameType out_point,
                FrameType framerate);
    ~Composition();

    int width() const { return m_width; }
    int height() const { return m_height; }

    FrameType in_point() const { return m_in_point; }
    FrameType out_point() const { return m_out_point; }
    FrameType framerate() const { return m_framerate; }

    const LayerList &layers() const { return m_layers; }
    void set_layers(LayerList &layers) { m_layers = std::move(layers); }

private:
    QString m_name;
    QString m_version;

    int m_width;
    int m_height;

    FrameType m_in_point;
    FrameType m_out_point;
    FrameType m_framerate;
    LayerList m_layers;
};

} // namespace eao

#endif // EAO_COMPOSITION_H
