#include "automatonconverter.h"
#include <qDebug>

/* Constructs a DFA from a NFA.
 * Uses subset construction, producing 2^n states where n is the number of states in the NFA.
 */

automatonConverter::automatonConverter(QVector <StateWidget *> stNFA, QVector <transitionwidget *> trNFA, QWidget *parent)
    : QWidget{parent}
{
    statesNFA = stNFA;
    transitionsNFA = trNFA;
    counter = 0;
}

void automatonConverter::convertNFA()
{
    // obtain state 0
    //statesDFA.push_back(startingState());
    QVector<QVector<State>> unmarkedStates;
    QVector<QString> alphabet;
    State st = startingState();
    QVector<State> stateSet;
    stateSet.push_back(st);
    statesDFA.push_back(st);
    int num = 0;
    // q0
    unmarkedStates.push_back(stateSet);

    for (auto& tr : transitionsNFA) {
        if (!alphabet.contains(tr->getLabel()) && (tr->getLabel() != "ε") && (tr->getLabel() != ' ')) {
            alphabet.append(tr->getLabel());
        }
    }
    //for (auto& a : unmarked) {
        //unmarkedStates.push_back(startingState());
        while (unmarkedStates.isEmpty() == false) {
            // same as marking a state
            unmarkedStates.removeOne(stateSet);
            num++;
            for (auto& a : alphabet) {
                QVector<State> tempSet = findReachableStates(stateSet, a.toStdString()[0]);
                QVector<State> eSet = epsilonClosure(tempSet);
                // obtain eSet's transitions for given input
                    //  QVector<Transition> newTr = findTransitions(st, a);

                // compress into new state for DFA
                State dState = compressStates(eSet);
                    for (auto& tr : transitionsNFA) {
                        for (auto& st : statesNFA) {

                            if ((tr->getLabel() == a) && (st->getId()) == tr->getStart().getId()) {
                                qInfo() <<  QString::fromStdString(dState.getName());
                                qInfo() <<  tr->getEnd().getId();
                                if (dState.getName().find(tr->getEnd().getId()) != string::npos) {

                                        for (auto& dSt: statesDFA) {
                                            if (dSt.getName().find(st->getState().getId()) != string::npos) {

                                                transitionsDFA.push_back(Transition(dSt, a.toStdString()[0], dState));
                                            }
                                        }
                                }

                            }
                    //if (!(QString::fromStdString(dfa.getName()).compare(QString::fromStdString(dState.getName())) == 0)) {
                     //   transitionsDFA.push_back(Transition(st, a.toStdString()[0], dState));


                        }

                    if (!statesDFA.contains(dState)) {
                        statesDFA.push_back(dState);
                    }
                }

                // if new unmarked state, add to transition
                if (!unmarkedStates.contains(eSet)) {
                    unmarkedStates.push_back(eSet);
                }

                //st = dState;


            }
            if (num > 2) {
                break;
            }
        }
    }


// Establishes the starting state for the DFA.
State automatonConverter::startingState()
{
    // obtain starting state
    State startState(counter);
  //  QVector <State> stateSet;
    //StateWidget startingState;
    for (auto& graphicalState : statesNFA) {
        if (graphicalState->getCurrent()) {
            startState = graphicalState->getState();
            break;
        }
    }
    // obtain e-closure of starting state
   // stateSet.push_back(startState);
    //stateSet = epsilonClosure(stateSet);
    counter++;
    return startState;
}

/*
 * Finds the epsilon closure of a set of states passed to the function.
 * Checks all possible e-move transitions for each state, adding new states linked via e-move to the set.
 * This continues until there are no more e-moves connecting to the set of states.
 */
QVector <State> automatonConverter::epsilonClosure(QVector <State> stateSet)
{
    // for each state in the set of states
    for (auto& state : stateSet) {
        // check for all possible epsilon moves in the set of transitions
        for (auto& transition : transitionsNFA) {
            // if epsilon move has been found, add to set of states, repeating until all epsilon moves have been found
            if ((state.getId() == transition->getStart().getId()) && (transition->getLabel() == "ε")) {
                // checking to prevent duplicates from being added
                if (!stateSet.contains(transition->getEnd().getState())) {
                    stateSet.push_back(transition->getEnd().getState());
                }
            }

        }
    }

    return stateSet;
}

// Takes a set of states, then simplifies said set into a single state for use by DFA.
State automatonConverter::compressStates(QVector <State> set)
{
    std::string identifier = "";
    bool isFinal = false;

    for (auto& state : set) {
            if (!QString::fromStdString(identifier).contains(QString::number(state.getId()))) {
                identifier.append(std::to_string(state.getId()));
            }
            if (state.getAccept() == true) {
                isFinal = true;
            }

    }
    State newState(counter, identifier);
    if (isFinal == true) {
        newState.setAccept(true);
    }

    counter++;
  //  newTransitions(set);

    return newState;
}

// Generates the list of transitions for a set of states.
/*QVector<Transition> automatonConverter::findTransitions(QVector<State> set, char input)
{
    QVector <Transition> newTr;
    for (auto& st : set) {
        for (auto& tr : transitionsNFA) {
            if (st == tr->getStart().getState()) {

                newTr.push_back(Transition(tr->getStart().getState(), tr->getLabel().toStdString()[0], tr->getEnd().getState()));
            }
        }
    }

    return newTr;
} */

// Returns all states connected to a provided state given a certain input symbol
QVector<State> automatonConverter::findReachableStates(QVector<State> stateSet, char input)
{
    QVector<State> resSet;

    for (auto& states : stateSet) {
        for (auto& tr : transitionsNFA) {
            if (tr->getLabel() == input && tr->getStart().getState() == states) {
                State temp = tr->getEnd().getState();
                if (!resSet.contains(temp)) {
                    resSet.push_back(tr->getEnd().getState());
                }
            }
        }
    }

        return resSet;
}

// only use after converting
QVector<State> automatonConverter::getStates()
{
    return statesDFA;
}

// only use after converting
QVector<Transition> automatonConverter::getTransitions()
{
    return transitionsDFA;
}
