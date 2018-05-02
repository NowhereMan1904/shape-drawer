#ifndef DOT_H
#define DOT_H

#include "myshape.h"

class Dot : public MyShape
{
public:
    enum { Type = UserType + 1 };

    Dot(const QPoint& p = QPoint{-1,-1});
    ~Dot() override;

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

    // access to representation
    QPoint& a();
    QPoint a() const;

    // Access to representation
    QPoint& rep() override;

    // enable use of qgraphicsitem_cast
    int type() const override;

private:
    QPoint _p;
};

#endif // DOT_H
