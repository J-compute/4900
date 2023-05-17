#include "nfa.h"
#include "string.h"
#include <iostream>
#include <sstream>

using namespace std;

// depreciated, only used for testing
// use inheritance if you ever intend on reusing this

NFA::NFA() {
}

NFA::NFA(std::vector<State> states, State initialState, std::string alpha) {
	this->states = states;
	this->initialState = initialState;
	
	string delimiter = ", ";
	std::stringstream ss(alpha);
	string temp = "";
	while (std::getline(ss, temp, ',')) {
		this->alphabet.push_back(temp);
	}
}

NFA::NFA(std::vector<State> states, State initialState, std::vector<State> final, std::string alpha, std::vector<Transition> transitions) {
	this->states = states;
	this->initialState = initialState;
	this->final = final;
	
	string delimiter = ", ";
	std::stringstream ss(alpha);
	string temp = "";
	while (std::getline(ss, temp, ',')) {
		this->alphabet.push_back(temp);
	}

	this->transitions = transitions;
}

NFA::NFA(NFA& other) {
	this->stateCount = other.stateCount;
	this->states = other.states;
	this->initialState = other.initialState;
	this->final = other.final;
	this->alphabet = other.alphabet;
	this->transitions = other.transitions;
}

NFA::~NFA() {
	states.clear();
	final.clear();
	alphabet.clear();
	transitions.clear();
}

void NFA::add(State state) {
	states.push_back(state);
}

void NFA::setInitial(State st) {
	initialState = st;
}

State NFA::getInitial() const {
	return initialState;
}

void NFA::setFinal(State state) {
	final.push_back(state);
}

std::vector<State> NFA::getFinal() const {
	return final;
}

void NFA::addTransition(Transition t) {
	transitions.push_back(t);
}

void NFA::addTransition(State src, char symbol, State dest) {
	Transition t(src, symbol, dest);
	transitions.push_back(t);
}

//std::vector<Transition> NFA::getTransition() {
//	return transitions;
//}

void NFA::viewTable() const {
	cout << "Delta: " << endl;
	for (auto& transition : transitions) {
		cout << transition << endl;
	}
}

std::vector<std::string> NFA::getAlphabet() const {
	return alphabet;
}

bool NFA::check(std::string input) {
	
	/*
	in concept, without e-moves:
		check all current states
			run all valid transitions for each current state
		at the end, check if any state reached the accepting state
	complexity comes from the acknowledgement of e-moves, which treat two states joined by the e-move as equal
	*/
	
	/*
	for current state
		for each e-move from that state, track in some set of states
		while there is another symbol:
		read next symbol
			create empty set
			check all transitions from the state
				add all e-move transitions to the set
				add all regular transitions to the set
			set becomes new current set
		do something with e-moves from transition destinations to another state:
			add the connected state to set of all states for this symbol?
			
	if set does not contain any accepting state, reject
	if set does contain at least one accepting state, accept
	*/
	bool accept = false;
	State currentState = initialState;	
	vector<State> currentSet;
	vector<State> stateSet;
	currentSet.push_back(currentState);
	
	for (auto& transition : transitions) {
		if ((currentState.getId() == transition.getSrc().getId()) && (transition.getName() == '=')) {
			currentSet.push_back(transition.getDest());
		}
	}
	
	for (unsigned int i = 0; i < input.length(); i++) {
		stateSet.clear();
		
		for (auto it : currentSet) {
			for (auto& transition : transitions) {
				
				if ((it.getId() == transition.getSrc().getId()) && (transition.getName() == '=')) {
					stateSet.push_back(transition.getDest());
				}
				if ((it.getId() == transition.getSrc().getId()) && (transition.getName() == input[i])) {
					stateSet.push_back(transition.getDest());
				}
			}
			
			for (auto& it : stateSet) {
				for (auto& transition : transitions) {
					
					if ((it.getId() == transition.getSrc().getId()) && (transition.getName() == '=')) {
						stateSet.push_back(transition.getDest());
					}
				}
			}
		}
		
		currentSet = stateSet;
	}
	
	for (auto it : currentSet) {
		if (it.getAccept() == true) {
			accept = true;
		}
	}
	if (accept == true) {
		cout << "Input " << input << " has been accepted." << endl;
	}
	if (accept == false) {
		cout << "Input " << input << " has been rejected." << endl;
	}
	return accept;
}

std::ostream &operator <<(std::ostream &os, const NFA& nfa) {
	os << "States: ";
	for (auto& st : nfa.states) {
		os << st.getId() << " ";
	}
	os << endl;
	os << "Alphabet: ";
		for (auto& a : nfa.getAlphabet()) {
		os << a << " ";
	}
	os << endl;
	
	nfa.viewTable();
	os << "Start State: " << nfa.getInitial().getId() << endl;
	os << "Accepting States: ";
	for (auto& fin : nfa.getFinal()) {
		os << fin.getId() << " " ;
	}
	os << endl;
	
	return os;
}
