#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPen>
//#include <QPixmap>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "qevent.h"
#include "State.h"
#include "StateWidget.h"
#include "Transition.h"
#include "NFA/nfa.h"
#include "DFA/dfa.h"
#include "transitionWidget.h"
#include "runautomaton.h"
#include "automatonconverter.h"
#include "qeventloop.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <QFile>
#include <QVector>
#include <QTimer>

class drawWidget : public QGraphicsView
{

public:
    drawWidget(QWidget *parent = nullptr);

    // adds a state or transition to the image
 //   void add(bool pressed);
    // removes a state or transition from the image
  //  void remove(bool pressed);
    // marks a state as either the initial state or an accepting state
    ~drawWidget();

    void saveToFile(QFile& file);
    void loadFromFile(QFile& file);

   void mark(bool pressed);

//    bool openAutomaton();
//    bool saveAutomaton();

    int getm();
    int counter;
    QString counter1;

    void addState();
    void addTransition();
    void moveState();
    void removeState();
    void removeTransition();
    void setStart();
    void setAccept();
    void setMode(int m);
    void setFA(QString text);
    void reverse();
    void clearAll();
    void convertFA();
    //void setCurrentState(StateWidget * current);
    bool execFA();
    StateWidget * obtainState();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
   // void paint() ;

private:
    QVector<StateWidget *> states; //= *new QVector<StateWidget *>;
    QVector<transitionwidget *> transitions;
  //  QVector<StateWidget *> newGraphicalStates = *new QVector<StateWidget *>;
  //  QVector<State> newStates;


    StateWidget * stateCopy;
    bool dfaMode = false;
    bool nfaMode = false;
 //   StateWidget * current;
 //   StateWidget * prev;

    // mode of left click
    QPainter painter;
    QGraphicsScene *sc;
    int mMode = 0;

    float mouseX = 0;
    float mouseY = 0;


public slots:
    void setCurrentState(StateWidget * current);
    void setCurrentStateSet(QVector<StateWidget *> current);

private slots:
    void zoomOut();
    void zoomIn();
};
#endif // DRAWWIDGET_H
