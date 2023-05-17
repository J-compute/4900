#include <iostream>

#include "Transition.h"

/* Basic class for the implementation of transition functions
 * Q x E --> P(Q)
 */

Transition::Transition(State src,  char input, State dest) {
	this->src = src;
	this->input = input;
	this->dest = dest;
}

Transition::~Transition(){
//	this->src = ;
	this->input = -1;
//	this->dest = NULL;
}

void Transition::setName(char input) {
	this->input = input;
}

char Transition::getName() const {
	return input;
}

State Transition::getSrc() const {
	return src;
}

State Transition::getDest() const {
	return dest;
}

/*  thrown together for minimization, don't use yet
 *	tests two transitions to see if they are equal
 *	return false if any section is found to be inequal, else return true
 */
 /*
bool Transition::equal(Transition &other) {
	if (!(this->src.getName().equals(other.src.getName()) && 
		this->src.getId() == other.src.getId()) {
		return false;
	}
	if (!(this->input != other.input;)) {
		return false;
	}
    if (!(this->dest.getName().equals(other.dest.getName()) && 
		this->dest.getId() == other.dest.getId()) {
		return false;
	}
	
	return true;
} */

// overloaded output

std::ostream &operator <<(std::ostream &os, const Transition &t) {
	os << t.getSrc().getId() << " | " << t.getName() << " | " << t.getDest().getId();
	return os;
}
