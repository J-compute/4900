#include "runautomaton.h"
#include "qeventloop.h"
#include "qtimer.h"

runAutomaton::runAutomaton(QString alpha, QString input, QVector<StateWidget *> statesFA, QVector<transitionwidget *> transitionFA, int mode, QWidget *parent)
    : QWidget{parent}
{
    modeFA = mode;
    alphabet = alpha;
    this->input = input;
    states = statesFA;
    transitions = transitionFA;
    current = &getInitialDFA();
    nextState.setInterval(1000);
    connect(&nextState, SIGNAL(timeout()), this, SLOT(goToNext()));

}

StateWidget& runAutomaton::getInitialDFA()
{
    nextState.start();
    for (auto& st : states) {
        if (st->getInit() == true) {
            return *st;
        }
    }
    for (auto& st : states) {
        return *st;
    }

}

QVector<StateWidget *> runAutomaton::getInitialNFA()
{
    QVector<StateWidget *> startSet;
    for (auto& st : states) {
        if (st->getInit() == true) {
            startSet.push_back(st);
        }
    }
    for (auto& tr : transitions) {
        for (auto& st : states) {
            if (tr->getStart().getId() == st->getId() && tr->getLabel() == "ε") {
                startSet.push_back(&tr->getEnd());
            }
        }
    }
    return startSet;
}

void runAutomaton::goToNext() {
    if (counter >= alphabet.length()) {
        check();
        return;
    }
    else {
        if (modeFA == 1) {
            if (prev != nullptr) {
                prev = current;
                prev->setCurrent(false);
            }
            for (auto& tr : transitions) {
                if (current->getId() == tr->getStart().getId() && tr->getLabel() == alphabet[counter]) {
                    current = &tr->getStart();
                    current->setCurrent(true);
                    break;
                }

            }
            counter++;
            current->update();
            QEventLoop loop;
            QTimer t;
            t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
            t.start(1000);
            loop.exec();
        }
    }

}

void runAutomaton::run()
{
    if (modeFA == 1) {
        runDFA();
    }
    else if (modeFA == 2) {
        runNFA();
    } else
        return;
}

bool runAutomaton::runDFA()
{
    StateWidget st = getInitialDFA();
    current = &st;
    /*for (auto& state : states) {
        if (state->getInit() == true) {
            current = state;
            break;
        }
    }*/

    if (current == nullptr) {
        return false;
    }
    if (alphabet == "") {
        for (auto& transition : transitions) {
            if (!alphabet.contains(transition->getLabel()) && transition->getLabel() != "ε") {
                alphabet.append(transition->getLabel());

            }
        }
    }

    nextState.start(1000);
    /*

        // parse transitions along the way to create alphabet
        // reject if invalid
        // convert into nfa or dfa if valid
    // request input

    for (unsigned int i = 0; i < input.length(); i++) {
        for (auto& transition : transitions) {
           // current->setCurrent(true);
            if (prev != nullptr) {
                prev = current;
                prev->setCurrent(false);
            }
            //QTimer::singleShot(1000, sc, SLOT(setCurrentState(current)));
           // QEventLoop loop1;
            //QTimer::singleShot(500, this, [this, current] () { drawWidget::setCurrentState(current);});
            //loop1.exec();
            goToNext();
            //cout << "Step 1" << endl;

            if (current->getId() == transition->getStart().getId()) {
                //cout << "Step 2" << endl;
                //cout << currentState.getId() << endl;
                // if state and symbol match, go to next state
                if (input[i] == transition->getLabel()) {
                    //cout << "Step 3" << endl;
                    prev = current;
                    prev->setCurrent(false);
                    current = &transition->getEnd();
                    //QTimer::singleShot(2000, this, [this, current] () { drawWidget::setCurrentState(current);});
                    //QEventLoop loop2;
                    //QTimer::singleShot(500, this, [this, current] () { drawWidget::setCurrentState(current);});
                    goToNext();

                    //cout << currentState.getId() << endl;
                    break;
                    // if end of input and in accept state, DFA accepts input

                }
            }
        }

        // if end of input and in accept state, DFA accepts input

        if ((input[i + 1] == '\0') && (current->getAccept() == true)) {
            current->setCurrent(false);
            return true;
            //current->setCurrent(false);
            break;
        }
    }

    current->setCurrent(false);
    return false;
    // run fa
        // accept if valid
        // reject if invalid ie no accepting state reached or string is longer than automaton

    */
     return true;
}

bool runAutomaton::runNFA()
{
    return true;
}

bool runAutomaton::check()
{
    if (modeFA == 1) {
        if (current->getAccept())
            return true;
        else
            return false;
    }
}

