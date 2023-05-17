#ifndef RUNAUTOMATON_H
#define RUNAUTOMATON_H

#include "StateWidget.h"
#include "qtimer.h"
#include "transitionWidget.h"
#include <QWidget>

class runAutomaton : public QWidget
{
    Q_OBJECT
public:
    explicit runAutomaton(QString alpha, QString input, QVector<StateWidget *> statesFA, QVector<transitionwidget *> transitionFA, int mode, QWidget *parent = nullptr);

    StateWidget& getInitialDFA();
    QVector<StateWidget *> getInitialNFA();

    void run();
    bool runDFA();
    bool runNFA();
    bool check();

public slots:
    void goToNext();

signals:

private:
    QTimer nextState;
    QString alphabet = "";
    int counter = 0;
    int modeFA = 0;
    QString input = "";
    QVector<StateWidget *> states;
    QVector<transitionwidget *> transitions;
    StateWidget * current = nullptr;
    StateWidget * prev = nullptr;

};

#endif // RUNAUTOMATON_H
