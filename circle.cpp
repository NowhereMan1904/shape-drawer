#include "circle.h"

#include <QPainter>


Circle::Circle(const QPoint& c, const QPoint& r)
    : _c{c}, _r{r}
{ }

QRectF Circle::boundingRect() const
{
    qreal penWidth = thickness();
    return QRectF{nw().x() - penWidth/2, nw().y() - penWidth/2,
                e().x()-w().x() + penWidth, s().y()-n().y() + penWidth};
}

void Circle::paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen{color(),
                         static_cast<qreal>(thickness()),
                         outline()});
    painter->drawEllipse(QRectF{nw(),se()});
}

QPoint Circle::n() const
{
    return QPoint{_c.x(),
                  static_cast<int>(_c.y() - QLineF{_c,_r}.length())};
}

QPoint Circle::s() const
{
    return QPoint{_c.x(),
                  static_cast<int>(_c.y() + QLineF{_c,_r}.length())};
}

QPoint Circle::w() const
{
    return QPoint{static_cast<int>(_c.x() - QLineF{_c,_r}.length()),
                  _c.y()};
}

QPoint Circle::e() const
{
    return QPoint{static_cast<int>(_c.x() + QLineF{_c,_r}.length()),
                  _c.y()};
}

QPoint Circle::ne() const
{
    qreal radium = QLineF{_c,_r}.length();
    return QPoint{static_cast<int>(_c.x() + radium),
                  static_cast<int>(_c.y() - radium)};
}

QPoint Circle::nw() const
{
    qreal radium = QLineF{_c,_r}.length();
    return QPoint{static_cast<int>(_c.x() - radium),
                  static_cast<int>(_c.y() - radium)};
}

QPoint Circle::se() const
{
    qreal radium = QLineF{_c,_r}.length();
    return QPoint{static_cast<int>(_c.x() + radium),
                  static_cast<int>(_c.y() + radium)};
}

QPoint Circle::sw() const
{
    qreal radium = QLineF{_c,_r}.length();
    return QPoint{static_cast<int>(_c.x() - radium),
                  static_cast<int>(_c.y() + radium)};
}

QPoint Circle::c() const
{
    return _c;
}

QPoint&Circle::c()
{
    prepareGeometryChange();
    return _c;
}

QPoint&Circle::r()
{
    prepareGeometryChange();
    return _r;
}

QPoint Circle::r() const
{
    return _r;
}

int Circle::type() const
{
    return Type;
}

Circle::~Circle() = default;
