#include "dot.h"
#include "line.h"
#include "rectangle.h"
#include "myshape.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
/*  House
    auto wall     = new Rectangle {QPoint{10, 180},
                                   QPoint{180,80 }};
    auto door     = new Rectangle {QPoint{80, 180},
                                   QPoint{110,130}};
    auto lwindow  = new Rectangle {QPoint{30, 130},
                                   QPoint{60, 110}};
    auto rwindow  = new Rectangle {QPoint{130,130},
                                   QPoint{160,110}};
    auto doorknob = new Dot       {QPoint{100,150}};
    auto lroof    = new Line      {QPoint{10, 80 },
                                   QPoint{95, 40 }};
    auto rroof    = new Line      {QPoint{95, 40 },
                                   QPoint{180,80 }};

    wall->setThickness(4);
    wall->setOutline(Qt::DashDotLine);
    doorknob->setThickness(5);
    lroof->setOutline(Qt::DashLine);
    rroof->setThickness(1);

    window->draw(wall);
    window->draw(door);
    window->draw(lwindow);
    window->draw(rwindow);
    window->draw(doorknob);
    window->draw(lroof);
    window->draw(rroof);
*/
    window.show();
    return QApplication::exec();
}

/*
 * BUG: Are MyShapes correctly destroyed? (probably yes)
 * FIXME: Android permissions and other settings
 * FIXME: call QGraphicsItem::prepareGeometryChange() in shape destructors
 * TODO: Text
 * TODO: QValidator class
 * TODO: Complete color combo box
 * TODO: Edit shapes
 */
