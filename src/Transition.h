#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"

class Transition {
	public:
		Transition(State src, char input, State dest);
		~Transition();
		
		void setName(char input);
		char getName() const;
		State getSrc() const;
		State getDest() const;
		
		// to be implemented later for minimization
//		bool equal(Transition &other);
		
		friend std::ostream &operator <<(std::ostream &os, const Transition &t);
		
	private:
		State src;
		char input;
		State dest;
		//std::map<std::pair<state, char>, state> transitionFunction
};

#endif
