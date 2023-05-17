#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>

class State {
	public:
		State();
		State(const State& state);
		State(int id);
		State(int id, std::string name);
		State(int id, bool accept);
		
		~State();		
		
		void setId(int id);
		void setName(std::string name);
		int getId() const;
		std::string getName() const;
		void setAccept(bool isAccept);
		bool getAccept() const;
		
		friend bool operator ==(const State &st1, const State &st2);
		friend std::ostream &operator <<(std::ostream &os, const State &st);
		
		
	private:
		int stateId;
		std::string stateName;
		bool isAccepting;
		
};

#endif
