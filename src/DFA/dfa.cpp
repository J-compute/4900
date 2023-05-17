#include "dfa.h"
#include "string.h"

#include <iostream>
#include <sstream>

using namespace std;

// depreciated, only used for testing

DFA::DFA() {
}

DFA::DFA(std::vector<State> states, State initialState, std::string alpha) {
	this->states = states;
	this->initialState = initialState;
	
	string delimiter = ", ";
	std::stringstream ss(alpha);
	string temp = "";
	while (std::getline(ss, temp, ',')) {
		this->alphabet.push_back(temp);
	}
}

DFA::DFA(std::vector<State> states, State initialState, std::vector<State> final, std::string alpha, std::vector<Transition> transitions) {
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

DFA::DFA(DFA& other) {
	this->stateCount = other.stateCount;
	this->states = other.states;
	this->initialState = other.initialState;
	this->final = other.final;
	this->alphabet = other.alphabet;
	this->transitions = other.transitions;
}

DFA::~DFA() {
	
}

void DFA::add(State state) {
	states.push_back(state);
}

//void DFA::remove(State state) {
//	if (int i = 0; i < states.size(); i++) {
//		if ()
//	}
//	state.setId(NULL);
//	state.setName('\0');
	
//}

void DFA::setInitial(State st) {
	initialState = st;
}

State DFA::getInitial() const {
	return initialState;
}

void DFA::setFinal(State state) {
	final.push_back(state);
}

std::vector<State> DFA::getFinal() const {
	return final;
//	for (auto& fin : final) {
//		cout << fin << " ";
//	}
}

// Adding transitions to the table
// Accounts for whether a certain transition object already exists
 
void DFA::addTransition(Transition t) {
	transitions.push_back(t);
}

void DFA::addTransition(State src, char symbol, State dest) {
	Transition t(src, symbol, dest);
	transitions.push_back(t);
}

// Display all currently added transitions

void DFA::viewTable() const {
	cout << "Delta: " << endl;
	for (auto& transition : transitions) {
		cout << transition << endl;
	}
}

std::vector<std::string> DFA::getAlphabet() const {
	return alphabet;
}

 // Run a provided input through the automaton 
 // If it can go from the initial state to any of the accepting states, return a confirmation
 // The input must not contain characters from outside of the DFA's assigned alphabet
 // Any text output will be cleaned up in the future
 
 
bool DFA::check(std::string input) {

	cout << "Running DFA on input: " << input << endl;
//	int current = 0;
	
	// validating string
/*	bool accepted = false;
	
		for (unsigned int i = 0; i < input.length(); i++) {
			accepted = false;
			string temp = input[i];
			for (auto& a : this->getAlphabet()) {
				input.find(a[0])
				if (strcmp(temp, a) == 0) {
					accepted = true;
				}
			}
		}
	
	if (accepted == false) {
		throw std::invalid_argument("Input contains characters not in the finite automaton's alphabet. Rejected." << endl;)
		
		return false;
	}
	*/

	//	transitions::iterator itr 
	
	// Run DFA until the input is over
	State currentState = initialState;	
	
	for (unsigned int i = 0; i < input.length(); i++) {
		
		// Go to starting state, then confirm that a transition from that state is possible
		
		for (auto& transition : transitions) {
			//cout << "Step 1" << endl;
	
			if (currentState.getId() == transition.getSrc().getId()) {
				//cout << "Step 2" << endl;
				//cout << currentState.getId() << endl;
				// if state and symbol match, go to next state
				if (input[i] == transition.getName()) {
					//cout << "Step 3" << endl;
					cout << "State " << currentState.getId() << " on " << transition.getName() << ": " << transition.getDest().getId() << endl;
					currentState = transition.getDest();
					//cout << currentState.getId() << endl;
					break;
					// if end of input and in accept state, DFA accepts input

				}
			}
		}
		
		// if end of input and in accept state, DFA accepts input
		
		if ((input[i + 1] == '\0') && (currentState.getAccept() == true)) {
			
			cout << "Success: input accepted on state " << currentState.getId() << endl;
			return true;
			break;
		}		
	}
	
	cout << "Failure: the input string has been rejected " << endl;
	
	return false;
}

// Overloaded to present all data on the automaton
// Primarily for testing
std::ostream &operator <<(std::ostream &os, const DFA& dfa) {
	os << "States: ";
	for (auto& st : dfa.states) {
		os << st.getId() << " ";
	}
	os << endl;
	os << "Alphabet: ";
		for (auto& a : dfa.getAlphabet()) {
		os << a << " ";
	}
	os << endl;
	
	dfa.viewTable();
	os << "Start State: " << dfa.getInitial().getId() << endl;
	os << "Accepting States: ";
	for (auto& fin : dfa.getFinal()) {
		os << fin.getId() << " " ;
	}
	os << endl;
	
	return os;
}
