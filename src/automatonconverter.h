#ifndef AUTOMATONCONVERTER_H
#define AUTOMATONCONVERTER_H

#include "StateWidget.h"
#include "transitionWidget.h"
#include <QWidget>
#include <QStack>
#include <QList>

using namespace std;

class automatonConverter : public QWidget
{
    Q_OBJECT
public:
    explicit automatonConverter(QVector <StateWidget *> stNFA, QVector <transitionwidget *> trNFA, QWidget *parent = nullptr);

    void convertNFA();
    State startingState();
    QVector <State> epsilonClosure(QVector <State> stateSet);
    State compressStates(QVector <State> set);
    QVector <Transition> findTransitions(QVector <State> set, char input);
    QVector <State> findReachableStates(QVector<State> stateSet, char input);
    QVector<State> getStates();
    QVector<Transition> getTransitions();
signals:

private:
    int counter;
    QVector <StateWidget *> statesNFA;
    QVector<transitionwidget *> transitionsNFA;
    QVector<State> statesDFA;
    QVector<StateWidget *> graphicalStatesDFA;
    QVector<Transition> transitionsDFA;
};

#endif // AUTOMATONCONVERTER_H
