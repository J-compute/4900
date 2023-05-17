#include "minimizer.h"



minimizer::minimizer()
{

}

// utilizes hopcroft's algorithm to minimize the states of a given dfa
/* P := {F, Q \ F}
W := {F, Q \ F}

while (W is not empty) do
    choose and remove a set A from W
    for each c in Σ do
        let X be the set of states for which a transition on c leads to a state in A
        for each set Y in P for which X ∩ Y is nonempty and Y \ X is nonempty do
            replace Y in P by the two sets X ∩ Y and Y \ X
            if Y is in W
                replace Y in W by the same two sets
            else
                if |X ∩ Y| <= |Y \ X|
                    add X ∩ Y to W
                else
                    add Y \ X to W
*/
void minimizer::minimizeDFA(QVector<StateWidget> states, QVector<transitionwidget *> transitions, QString alphabet)
{
    // accept states
    QList<State> F;
    for (auto& st : states) {
        if (st.getAccept() == true) {
            F.append(st.getState());
        }
    }
    // all states
    QList<State> Q;
    for (auto& st : states) {
        Q.append(st.getState());
    }

    //P := {F, Q \ F}
    //W := {F, Q \ F}
    QList<QList<State>> P;
    QList<QList<State>> W;
    P += F;
    P += Q;
    W += F;
    W += Q;

    while (!W.isEmpty()) {
        QList<State> A = W.front();
        W.pop_front();
        for (int i = 0; i < alphabet.length(); i++) {
            //let X be the set of states for which a transition on c leads to a state in A
            QList<State> X;
            for (auto& tr : transitions) {
                if (tr->getLabel() == alphabet[i] && A.contains(tr->getEnd().getState())) {
                    X.append(tr->getStart().getState());
                }
            }
            //for each set Y in P for which X ∩ Y is nonempty and Y \ X is nonempty do
            for (int j = 0; j < P.size() - 1; j++) {
                //replace Y in P by the two sets X ∩ Y and Y \ X
                QList<State> Y = P[j];

                //if Y is in W
                //    replace Y in W by the same two sets
                //else
                //    if |X ∩ Y| <= |Y \ X|
                //        add X ∩ Y to W
                //   else
                //        add Y \ X to W
            }

        }
   }

}
