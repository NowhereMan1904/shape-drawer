#include "rectangle.h"

#include <QPainter>

Rectangle::Rectangle(const QPoint& a, const QPoint& b)
    : _a{a}, _b{b}
{ }

QRectF Rectangle::boundingRect() const
{
    qreal penWidth = thickness();
    return QRectF{nw().x() - penWidth/2, nw().y() - penWidth/2,
                  e().x()-w().x() + penWidth, s().y()-n().y() + penWidth};
}

void Rectangle::paint(QPainter* painter,
                      const QStyleOptionGraphicsItem* option,
                      QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{color(),
                         static_cast<qreal>(thickness()),
                         outline()});
    painter->drawRect(QRect{_a,_b});
}

QPoint Rectangle::n() const
{
    return QPoint{
        (_a.x()+_b.x())/2,
        _a.y() <= _b.y() ? _a.y() : _b.y()
    };
}

QPoint Rectangle::s() const
{
    return QPoint{
        (_a.x()+_b.x())/2,
        _a.y() >= _b.y() ? _a.y() : _b.y()
    };
}

QPoint Rectangle::w() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                (_a.y()+_b.y())/2
    };
}

QPoint Rectangle::e() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                (_a.y()+_b.y())/2
    };
}

QPoint Rectangle::ne() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                _a.y() <= _b.y() ? _a.y() : _b.y()
    };
}

QPoint Rectangle::nw() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                _a.y() <= _b.y() ? _a.y() : _b.y()
    };
}

QPoint Rectangle::se() const
{
    return QPoint{
                _a.x() >= _b.x() ? _a.x() : _b.x(),
                _a.y() >= _b.y() ? _a.y() : _b.y()
    };
}

QPoint Rectangle::sw() const
{
    return QPoint{
                _a.x() <= _b.x() ? _a.x() : _b.x(),
                _a.y() >= _b.y() ? _a.y() : _b.y()
};
}

QPoint Rectangle::c() const
{
    return QPoint{
                (_a.x()+_b.x())/2,
                (_a.y()+_b.y())/2,
    };
}

Rectangle::~Rectangle() = default;

QPoint& Rectangle::a()
{
    prepareGeometryChange();
    return _a;
}

QPoint& Rectangle::b()
{
    prepareGeometryChange();
    return _b;
}

QPoint Rectangle::a() const
{
    return _a;
}

QPoint Rectangle::b() const
{
    return _b;
}

QPoint& Rectangle::rep()
{
    return b();
}

int Rectangle::type() const
{
    return Type;
}
