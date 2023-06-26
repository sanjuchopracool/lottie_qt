#include "composition.h"
#include "Layers/LayerFactory.h"

using namespace std;
namespace eao {

Composition::Composition(QString name,
                         QString version,
                         int width,
                         int height,
                         FrameType in_point,
                         FrameType out_point,
                         FrameType framerate)
    : m_name(std::move(name))
    , m_version(std::move(version))
    , m_width(width)
    , m_height(height)
    , m_in_point(in_point)
    , m_out_point(out_point)
    , m_framerate(framerate)
{}

Composition::~Composition() {}

} // namespace eao
