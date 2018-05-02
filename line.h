#ifndef LINE_H
#define LINE_H

#include "myshape.h"

class Line : public MyShape
{
public:
    enum { Type = UserType + 2 };

    Line(const QPoint& a = QPoint{-1,-1},
         const QPoint& b = QPoint{-1,-1});

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
    ~Line() override;

    // access to representation
    QPoint& a();
    QPoint& b();

    QPoint a() const;
    QPoint b() const;

    // Access to representation
    QPoint& rep() override;

    // enable use of qgraphicsitem_cast
    int type() const override;

private:
    QPoint _a,_b;
};

#endif // LINE_H
