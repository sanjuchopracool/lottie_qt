#ifndef EAO_COMPOSITION_H
#define EAO_COMPOSITION_H

#include "Layers/LayerModel.h"
#include "lottielib.h"
#include <memory>
#include <vector>

namespace eao {

class Composition
{
public:
    using LayerModelPtr = std::unique_ptr<LayerModel>;
    using LayerModelList = std::vector<LayerModelPtr>;

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

    const LayerModelList &layers() const { return m_layers; }
    void set_layers(LayerModelList &layers) { m_layers = std::move(layers); }

private:
    QString m_name;
    QString m_version;

    int m_width;
    int m_height;

    FrameType m_in_point;
    FrameType m_out_point;
    FrameType m_framerate;
    LayerModelList m_layers;
};

} // namespace eao

#endif // EAO_COMPOSITION_H
