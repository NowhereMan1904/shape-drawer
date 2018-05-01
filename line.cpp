#include "line.h"

#include <QPainter>

Line::Line(const QPoint& a, const QPoint& b)
    : _a{a}, _b{b}
{ }

QRectF Line::boundingRect() const
{
    qreal penWidth = thickness();
    return QRectF{nw().x() - penWidth/2, nw().y() - penWidth/2,
                  e().x()-w().x() + penWidth, s().y()-n().y() + penWidth};
}

void Line::paint(QPainter* painter,
                 const QStyleOptionGraphicsItem* option,
                 QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{color(),
                         static_cast<qreal>(thickness()),
                         outline()});
    painter->drawLine(_a,_b);
}

QPoint Line::n() const
{
    return QPoint{
                (_a.x()+_b.x())/2,
                _a.y() <= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::s() const
{
    return QPoint{
                (_a.x()+_b.x())/2,
                _a.y() >= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::w() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                (_a.y()+_b.y())/2
                };
}

QPoint Line::e() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                (_a.y()+_b.y())/2
                };
}

QPoint Line::ne() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                _a.y() <= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::nw() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                _a.y() <= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::se() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                _a.y() >= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::sw() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                _a.y() >= _b.y() ? _a.y() : _b.y()
                };
}

QPoint Line::c() const
{
    return QPoint{
                (_a.x()+_b.x())/2,
                (_a.y()+_b.y())/2,
    };
}

Line::~Line() = default;

QPoint& Line::a()
{
    prepareGeometryChange();
    return _a;
}

QPoint& Line::b()
{
    prepareGeometryChange();
    return _b;
}

QPoint Line::a() const
{
    return _a;
}

QPoint Line::b() const
{
    return _b;
}

int Line::type() const
{
    return Type;
}
