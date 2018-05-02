#include "dot.h"

#include <QPainter>

Dot::Dot(const QPoint& p)
    : _p{p}
{ }

Dot::~Dot() = default;

QRectF Dot::boundingRect() const
{
    qreal penWidth = thickness();
    return QRectF{_p.x() - penWidth/2, _p.y() - penWidth/2,
                  1 + penWidth, 1 + penWidth};
}

void Dot::paint(QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{color(),
                         static_cast<qreal>(thickness()),
                         outline()});
    painter->drawPoint(_p);
}

QPoint Dot::n() const
{
    return _p;
}

QPoint Dot::s() const
{
    return _p;
}

QPoint Dot::w() const
{
    return _p;
}

QPoint Dot::e() const
{
    return _p;
}

QPoint Dot::ne() const
{
    return _p;
}

QPoint Dot::nw() const
{
    return _p;
}

QPoint Dot::se() const
{
    return _p;
}

QPoint Dot::sw() const
{
    return _p;
}

QPoint Dot::c() const
{
    return _p;
}

QPoint& Dot::a()
{
    prepareGeometryChange();
    return _p;
}

QPoint Dot::a() const
{
    return _p;
}

QPoint& Dot::rep()
{
    return a();
}

int Dot::type() const
{
    return Type;
}
