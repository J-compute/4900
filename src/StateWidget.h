#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "State.h"
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QColor>
#include <QFont>

class StateWidget : public QGraphicsObject
{
    public:
        StateWidget();
        StateWidget(State st, float x, float y); //  QGraphicsItem *parent = nullptr
        StateWidget(State st);
        ~StateWidget();
        StateWidget(const StateWidget &st); //  QGraphicsItem *parent = nullptr

        bool getAccept();
        State getState() const;
        bool getInit();
        int getId() const;
        bool getCurrent();
        float getX();
        float getY();
        void setAccept(bool accept);
        void setInit(bool init);
        void setCurrent(bool cur);
        void setPosition(float x, float y);
        void relocate(QPointF pos);
        void onMouseClick();
        void modify();
       // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
       // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

        friend bool operator ==(const StateWidget &st1, const StateWidget &st2);
    protected:
       QRectF boundingRect() const override;
       void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        //QRectF ;

    private:
        State state;
        float stateX;
        float stateY;
        QString name;
        bool start;
        bool final;
        bool current;
        int id;
        bool held = false;
        QColor border = Qt::black;
        QColor stColor;
};

#endif // STATEWIDGET_H
