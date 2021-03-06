#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStack>
#include <QButtonGroup>
#include <QIcon>
#include <QComboBox>

#include "myshape.h"
#include "view.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    enum class Mode { insDot, insLine, insRect, insCircle, edit };

    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void draw(MyShape* shape);

    void buttonGroupClicked(int);

    void onMouseClick(QPoint);
    void onMouseMove(QPoint);

    void undo();
    void redo();

private:
    void createButtons();
    void createOptions();
    QIcon createThickIcon(int);
    void createOutlineCombo();
    QIcon createOutlineIcon(Qt::PenStyle);
    void createColorCombo();
    QIcon createColorIcon(Qt::GlobalColor);

    view* _view;
    QGraphicsScene* _scene;
    QButtonGroup* _buttonGroup;
    QWidget* buttonWidget;
    QWidget* optionWidget;

    MyShape* tempShape;

    QComboBox* thickCombo;
    QComboBox* outCombo;
    QComboBox* colorCombo;

    QStack<MyShape*> undoStack;
    QStack<MyShape*> redoStack;

    Mode mode;
};

#endif // MAINWINDOW_H
