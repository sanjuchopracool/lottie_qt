#include "CompositionLayer.h"
#include "../Model/Layers/LayerModel.h"
#include <QDebug>
#include <QPainter>

#include "../NodeRenderSystem/NodeProperties/ValueProviders/KeyFrameValueProvider.h"

namespace Lottie {

void PaintBuffer::update_buffer_info(const PaintBufferInfo &info)
{
    m_buffer_info = info;
    m_pixmap = QPixmap(info.m_size);
    m_pixmap.fill(Qt::transparent);
}

void PaintBuffer::draw(QPainter *painter, FrameType t) const
{
    Q_UNUSED(t)
    painter->drawPixmap(m_pixmap.rect(), m_pixmap);
}

std::unique_ptr<QPainter> PaintBuffer::painter(FrameType)
{
    m_pixmap.fill(Qt::transparent);
    auto painter = std::make_unique<QPainter>(&m_pixmap);
    painter->scale(m_buffer_info.m_scale_x, m_buffer_info.m_scale_y);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    return painter;
}

void PaintBuffer::save()
{
    static int counter = 1;
    m_pixmap.save(QString("File_%1.png").arg(counter++));
}

CompositionLayer::CompositionLayer(const PaintBufferInfo& info)
{
    update_buffer_info(info);
}

}
