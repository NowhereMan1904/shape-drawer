#include "view.h"

view::view(QWidget* parent)
    : QGraphicsView {parent}
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setFrameShape(QGraphicsView::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(500,500);
}

void view::mousePressEvent(QMouseEvent* event)
{
    emit mouseClick(event->pos());
//    update();
}

void view::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMove(event->pos());
//    update();
}
