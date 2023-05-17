#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <QWidget>
#include "State.h"
#include "StateWidget.h"
#include "Transition.h"
#include "transitionWidget.h"

class minimizer
{
public:
    minimizer();
    void minimizeDFA(QVector<StateWidget> states, QVector<transitionwidget *> transitions, QString alphabet);

};

#endif // MINIMIZER_H
