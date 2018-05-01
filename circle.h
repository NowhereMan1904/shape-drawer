#ifndef CIRCLE_H
#define CIRCLE_H

#include "myshape.h"

class Circle : public MyShape
{
public:
    enum { Type = UserType + 4 };

    Circle(const QPoint& c = QPoint{-1,-1},
           const QPoint& r = QPoint{-1,-1});

    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

    // contact points
    QPoint n()  const override;
    QPoint s()  const override;
    QPoint w()  const override;
    QPoint e()  const override;
    QPoint ne() const override;
    QPoint nw() const override;
    QPoint se() const override;
    QPoint sw() const override;
    QPoint c()  const override;

    // destructor
    ~Circle() override;

    // access to representation
    QPoint& c();
    QPoint& r();

    QPoint r() const;

    // enable use of qgraphicsitem_cast
    int type() const override;

private:
    QPoint _c,_r;
};

#endif // CIRCLE_H
