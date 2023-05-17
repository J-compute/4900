#ifndef DFA_H
#define DFA_H

#include "../State.h"
#include "../Transition.h"

#include <vector>


//typedef std::map<std::pair<state, char> state> transition;

class DFA {
	public:
	    DFA();
		DFA(std::vector<State> states, State initialState, std::string alphabet);
		DFA(std::vector<State> states, State initialState, std::vector<State> final, std::string alphabet, std::vector<Transition> transitions);
		DFA(DFA& other);
		
		~DFA();
		
		void add(State state);
//		void remove(State state);
		void setInitial(State st);
		State getInitial() const;
		void setFinal(State state);
		std::vector<State> getFinal() const;
		void addTransition(Transition t);
		void addTransition(State src, char symbol, State dest);
		void viewTable() const;
		std::vector<std::string> getAlphabet() const;
		bool check(std::string input);
		
		friend std::ostream &operator <<(std::ostream &os, const DFA& dfa);
		
		
	private:
		int stateCount = 0;
		std::vector<State> states;
		State initialState;
		std::vector<State> final;
		std::vector<std::string> alphabet;
		std::vector<Transition> transitions;
		
		//std::map<std::pair<state, char>, state> transition;
		
};

#endif
