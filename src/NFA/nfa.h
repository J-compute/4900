#ifndef NFA_H
#define NFA_H

#include "../State.h"
#include "../Transition.h"

#include <vector>

/* A NFA involves a structure similar to the DFA, except it allows for epsilon moves and performs nondeterministic checking.
 * To implement it, check for the existence of the epsilon moves and find a way to examine two or more transitions sharing source and symbol simultaneously 
 * We may not always wish to simply use a DFA because of the complexity from an increased number of states
*/
class NFA {
	public:
	    NFA();
		NFA(std::vector<State> states, State initialState, std::string alphabet);
		NFA(std::vector<State> states, State initialState, std::vector<State> final, std::string alphabet, std::vector<Transition> transitions);
		NFA(NFA& other);
		
		~NFA();
		
		void add(State state);
		void setInitial(State st);
		State getInitial() const;
		void setFinal(State state);
		std::vector<State> getFinal() const;
		void addTransition(Transition t);
		void addTransition(State src, char symbol, State dest);
//        std::vector<Transition> getTransition() const;
		void viewTable() const;
		std::vector<std::string> getAlphabet() const;
		bool check(std::string input);
		
		friend std::ostream &operator <<(std::ostream &os, const NFA& nfa);
	private:
		int stateCount;
		std::vector<State> states;
		State initialState;
		std::vector<State> final;
		std::vector<std::string> alphabet;
		std::vector<Transition> transitions;
};

#endif
