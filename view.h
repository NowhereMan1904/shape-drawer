#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QInputEvent>

class view : public QGraphicsView
{
    Q_OBJECT

public:
    view(QWidget* parent = nullptr);

signals:
    void mouseClick(QPoint);
    void mouseMove(QPoint);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // VIEW_H
