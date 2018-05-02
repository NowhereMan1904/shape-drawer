#ifndef MYSHAPE_H
#define MYSHAPE_H

#include <QGraphicsItem>

class MyShape : public QGraphicsItem
{
public:
    MyShape() : thick{2}, out{Qt::SolidLine}, col{Qt::black} {}

    QRectF boundingRect() const override =0;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override =0;

    // contact points
    virtual QPoint n()  const =0;
    virtual QPoint s()  const =0;
    virtual QPoint w()  const =0;
    virtual QPoint e()  const =0;
    virtual QPoint ne() const =0;
    virtual QPoint nw() const =0;
    virtual QPoint se() const =0;
    virtual QPoint sw() const =0;
    virtual QPoint c()  const =0;

    // destructor
    ~MyShape() override = default;

    void setOutline(Qt::PenStyle outline = Qt::SolidLine) {
        if (outline>0 && outline<6)
            out = outline;
    }

    void setThickness(int i = 2) {
        if (i>=0)
            thick = i;
    }

    void setColor(Qt::GlobalColor color = Qt::black) {
        if (color>1 && color<19)
            col = color;
    }

    int thickness() const { return thick; }
    Qt::PenStyle outline() const { return out; }
    Qt::GlobalColor color() const { return col; }

    // Access to representation
    virtual QPoint& rep() = 0;

private:
    int thick;
    Qt::PenStyle out;
    Qt::GlobalColor col;
};

#endif // MYSHAPE_H
