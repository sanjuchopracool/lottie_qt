#ifndef PAINTING_ELEMENT_H
#define PAINTING_ELEMENT_H

class QPainter;

namespace eao {

class PaintingElement
{
public:
    virtual ~PaintingElement() {}
    virtual void draw(QPainter *painter, int parent_alpha) = 0;
};

} // namespace eao

#endif // PAINTING_ELEMENT_H
