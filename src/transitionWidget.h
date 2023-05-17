#ifndef TRANSITIONWIDGET_H
#define TRANSITIONWIDGET_H

#include <QWidget>
#include "StateWidget.h"
#include "Transition.h"
#include <QtMath>

class transitionwidget : public QGraphicsObject
{
public:
    transitionwidget();
    transitionwidget(StateWidget* state1, StateWidget* state2, QString label);
    transitionwidget(transitionwidget const &tr);
    ~transitionwidget();
    StateWidget& getStart();
    StateWidget& getEnd();
    QString getLabel();
    void createPath();
    float findDistance(QPoint qp);
    bool withinPoint(QPoint qp);
protected:
   QRectF boundingRect() const override;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    int length;
    StateWidget *stateStart;
    QString label;
    StateWidget *stateEnd;
    QPointF pointStart;
    QPointF pointEnd;

};

#endif // TRANSITIONWIDGET_H
