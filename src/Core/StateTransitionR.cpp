/* 
 * File:   StateTransitionR.cpp
 * Author: merlin
 * 
 * Created on May 20, 2012, 3:35 PM
 */

#include "StateTransitionR.h"

StateTransitionR::StateTransitionR(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::RECOVERED, random, state_transition_list, config) {
}

StateTransitionR::StateTransitionR(const StateTransitionR& orig) {
}

StateTransitionR::~StateTransitionR() {
}

NextState StateTransitionR::GetNextState(Person* person) const {
    return NextState(0, HostState::RECOVERED);
}