
/* finds the e-closure
 * that is, all states that are connected to a given state by epsilon transitions
 * always include the state itself
 */
 
void closure (State st, vector<State> trSet, vector<State> newSet) {
	// from state, run through list of transitions
	// collect all e-moves
	vector<State> closureSet;
	for (auto& transition : trSet) {
		if ((st.getId() == transition.getSrc().getId()) && (transition.getName() == '=')) {
			closureSet.push_back(transition.getDest());
		}
	}
	
	newSet.push_back(closureSet);
}


/* converts a nondetermistic finite automata into a deterministic finite automata
 * the result should be 2^n states where n is the number of states in the nfa
 * check for epsilon-moves
 */
 
DFA converter(NFA nfa) {
	
}
