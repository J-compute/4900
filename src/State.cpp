#include "State.h"

/*
 * Class for finite automaton states
*/

State::State() {
    stateName = '\0';
    stateId = -1;
    isAccepting = false;
}

State::State(int id) {
    stateName = '\0';
    stateId = id;
    isAccepting = false;
}

State::State(int id, bool accept) {
    stateName = '\0';
    stateId = id;
    isAccepting = accept;
}

// Copy constructor
State::State(const State& st) {
    this->stateId = st.stateId;
    this->stateName = st.stateName;
    this->isAccepting = st.isAccepting;
}
State::State(int id, std::string name) {
    this->stateId = id;
    this->stateName = name;
    this->isAccepting = false;
}

State::~State() {
    stateName = '\0';
    stateId = -1;
    isAccepting = false;
}

void State::setId(int id) {
    stateId = id;
}
void State::setName(std::string name) {
    stateName = name;
}
int State::getId() const {
    return stateId;
}
std::string State::getName() const {
    return stateName;
}
void State::setAccept(bool isAccept) {
    this->isAccepting = isAccept;
}
bool State::getAccept() const {
    return isAccepting;
}

bool operator ==(const State &st1, const State &st2) {
    //&& (st1.getName().compare(st2.getName()) == 0)
    //&& st1.getAccept() == st2.getAccept()
    if (st1.getId() == st2.getId()) {
        return true;
    }
    return false;
}

std::ostream &operator <<(std::ostream &os, const State &st) {
    os << st.getName();
    return os;
}
