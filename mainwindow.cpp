#include "mainwindow.h"
#include "dot.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"

#include <QLayout>
#include <QApplication>
#include <QInputEvent>
#include <QPushButton>
#include <QLabel>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget {parent},
      _view {new view},
      _scene {new QGraphicsScene},
      _buttonGroup {new QButtonGroup},
      buttonWidget {new QWidget},
      optionWidget {new QWidget},
      tempShape {nullptr},
      thickSlider {new QSlider{Qt::Horizontal}},
      outSlider {new QSlider{Qt::Horizontal}},
      colorSlider {new QSlider{Qt::Horizontal}},
      thickCombo {new QComboBox},
      outCombo {new QComboBox},
      colorCombo {new QComboBox},
      mode {Mode::edit}
{
    setWindowTitle("Shape painter");

    createButtons();
    createOptions();

    _scene->setSceneRect(0,0,500,500);
    _view->setScene(_scene);

    connect(_view, &view::mouseClick,
            this, &MainWindow::onMouseClick);
    connect(_view, &view::mouseMove,
            this, &MainWindow::onMouseMove);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(_view,1);
    mainLayout->addWidget(optionWidget);
    mainLayout->addWidget(buttonWidget);

    setLayout(mainLayout);
}

void MainWindow::draw(MyShape* shape)
{
    _scene->addItem(shape);
    undoStack << shape;
    _buttonGroup->button(2)->setEnabled(true);
    if (!redoStack.isEmpty()) {
        qDeleteAll(redoStack);
        redoStack.clear();
        _buttonGroup->button(3)->setEnabled(false);
    }
}

void MainWindow::buttonGroupClicked(int i)
{
    switch (i) {
    case 2: // undo
        undo();
        break;
    case 3: // redo
        redo();
        break;
    case Dot::Type:
        mode = Mode::insDot;
        break;
    case Line::Type:
        mode = Mode::insLine;
        break;
    case Rectangle::Type:
        mode = Mode::insRect;
        break;
    case Circle::Type:
        mode = Mode::insCircle;
        break;
    default:
        break;
    }
}

void MainWindow::onMouseClick(QPoint pos)
{
    switch (mode) {
    case Mode::insDot:
        tempShape = new Dot{pos};
        break;
    case Mode::insLine:
        tempShape = new Line{pos,pos};
        break;
    case Mode::insRect:
        tempShape = new Rectangle{pos,pos};
        break;
    case Mode::insCircle:
        tempShape = new Circle{pos,pos};
    default:
        break;
    }

    if (tempShape) {
        tempShape->setThickness(thickCombo->currentData().toInt());
        tempShape->setOutline(static_cast<Qt::PenStyle>(
                                  outCombo->currentData().toInt()));
        tempShape->setColor(static_cast<Qt::GlobalColor>(
                                colorCombo->currentData().toInt()));
        draw(tempShape);
    }
}

void MainWindow::onMouseMove(QPoint pos)
{
    switch (mode) {
    case Mode::insDot:
        qgraphicsitem_cast<Dot*>(tempShape)->a() = pos;
        break;
    case Mode::insLine:
        qgraphicsitem_cast<Line*>(tempShape)->b() = pos;
        break;
    case Mode::insRect:
        qgraphicsitem_cast<Rectangle*>(tempShape)->b() = pos;
        break;
    case Mode::insCircle:
        qgraphicsitem_cast<Circle*>(tempShape)->r() = pos;
        break;
    default:
        break;
    }
}

void MainWindow::undo()
{
    if (!undoStack.isEmpty()) {
        MyShape* shape = undoStack.pop();
        shape->hide();
        redoStack << shape;
        _buttonGroup->button(3)->setEnabled(true);
    }
    if (undoStack.isEmpty())
        _buttonGroup->button(2)->setEnabled(false);
}

void MainWindow::redo()
{
    if (!redoStack.isEmpty()) {
        MyShape* shape = redoStack.pop();
        shape->show();
        undoStack << shape;
        _buttonGroup->button(2)->setEnabled(true);
    }
    if (redoStack.isEmpty())
        _buttonGroup->button(3)->setEnabled(false);
}

void MainWindow::createButtons()
{
    auto buttonLayout = new QGridLayout;

    QPixmap dotPixmap(50,50);
    dotPixmap.fill(Qt::transparent);
    QPainter dotPainter(&dotPixmap);
    dotPainter.setPen(QPen{Qt::black, 20});
    dotPainter.drawPoint(25,25);
    auto dotButton  = new QPushButton(dotPixmap, "Dot");
    dotButton->setCheckable(true);

    QPixmap linePixmap(50,50);
    linePixmap.fill(Qt::transparent);
    QPainter linePainter(&linePixmap);
    linePainter.setPen(QPen{Qt::black, 4});
    linePainter.drawLine(5,5,45,45);
    auto lineButton = new QPushButton(linePixmap, "Line");
    lineButton->setCheckable(true);

    QPixmap rectPixmap(50,50);
    rectPixmap.fill(Qt::transparent);
    QPainter rectPainter(&rectPixmap);
    rectPainter.setPen(QPen{Qt::black, 4});
    rectPainter.drawRect(5,10,40,30);
    auto rectButton = new QPushButton(rectPixmap, "Rectangle");
    rectButton->setCheckable(true);

    QPixmap circlePixmap(50,50);
    circlePixmap.fill(Qt::transparent);
    QPainter circlePainter(&circlePixmap);
    circlePainter.setPen(QPen{Qt::black, 4});
    circlePainter.drawEllipse(5,5,40,40);
    auto circleButton = new QPushButton(circlePixmap, "Circle");
    circleButton->setCheckable(true);

    auto undoButton = new QPushButton(QIcon{":/undo.png"}, "Undo");
    undoButton->setEnabled(false);
    auto redoButton = new QPushButton(QIcon{":/redo.png"}, "Redo");
    redoButton->setEnabled(false);

    buttonLayout->addWidget(dotButton,  0, 0);
    buttonLayout->addWidget(lineButton, 1, 0);
    buttonLayout->addWidget(rectButton, 0, 1);
    buttonLayout->addWidget(circleButton, 1, 1);
    buttonLayout->addWidget(undoButton, 0, 2);
    buttonLayout->addWidget(redoButton, 1, 2);
    buttonWidget->setLayout(buttonLayout);

    _buttonGroup->addButton(dotButton,  Dot::Type);
    _buttonGroup->addButton(lineButton, Line::Type);
    _buttonGroup->addButton(rectButton, Rectangle::Type);
    _buttonGroup->addButton(circleButton, Circle::Type);
    _buttonGroup->addButton(undoButton, 2);
    _buttonGroup->addButton(redoButton, 3);

    connect(_buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);
}

void MainWindow::createOptions()
{
    // Thickness
    for (int i=0; i!=11; ++i)
        thickCombo->addItem(QString::number(i), i);
    thickCombo->setCurrentIndex(4);
    auto thickLabel = new QLabel{"Thickness"};
    auto thickLayout = new QVBoxLayout;
    thickLayout->addWidget(thickLabel);
    thickLayout->addWidget(thickCombo);

    // Outline
    createOutlineCombo();
    auto outLabel = new QLabel{"Outline"};
    auto outLayout = new QVBoxLayout;
    outLayout->addWidget(outLabel);
    outLayout->addWidget(outCombo);

    // Color
    createColorCombo();
    auto colorLabel = new QLabel{"Color"};
    auto colorLayout = new QVBoxLayout;
    colorLayout->addWidget(colorLabel);
    colorLayout->addWidget(colorCombo);

    auto layout = new QHBoxLayout;
    layout->addLayout(thickLayout);
    layout->addLayout(outLayout);
    layout->addLayout(colorLayout);
    optionWidget->setLayout(layout);
}

void MainWindow::createOutlineCombo()
{
    outCombo->addItem("Solid", 1);
    outCombo->addItem("Dash", 2);
    outCombo->addItem("Dot", 3);
    outCombo->addItem("Dash - Dot", 4);
    outCombo->addItem("Dash - Dot - Dot", 5);
}

void MainWindow::createColorCombo()
{
    colorCombo->addItem(createColorIcon(Qt::black),
                        "Black",
                        static_cast<int>(Qt::black));
    colorCombo->addItem(createColorIcon(Qt::gray),
                        "Gray",
                        static_cast<int>(Qt::gray));
    colorCombo->addItem(createColorIcon(Qt::white),
                        "White",
                        static_cast<int>(Qt::white));
    colorCombo->addItem(createColorIcon(Qt::red),
                        "Red",
                        static_cast<int>(Qt::red));
    colorCombo->addItem(createColorIcon(Qt::green),
                        "Green",
                        static_cast<int>(Qt::green));
    colorCombo->addItem(createColorIcon(Qt::blue),
                        "Blue",
                        static_cast<int>(Qt::blue));
    colorCombo->addItem(createColorIcon(Qt::cyan),
                        "Cyan",
                        static_cast<int>(Qt::cyan));
    colorCombo->addItem(createColorIcon(Qt::magenta),
                        "Magenta",
                        static_cast<int>(Qt::magenta));
    colorCombo->addItem(createColorIcon(Qt::yellow),
                        "Yellow",
                        static_cast<int>(Qt::yellow));
}

QIcon MainWindow::createColorIcon(Qt::GlobalColor color)
{
    QPixmap icon(50,50);
    QPainter painter(&icon);
    painter.setBrush(color);
    painter.drawRect(0,0,50,50);
    return icon;
}
