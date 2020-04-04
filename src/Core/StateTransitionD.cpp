/* 
 * File:   StateTransitionD.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 12:51 PM
 */

#include "StateTransitionD.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"

StateTransitionD::StateTransitionD(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::DEATH, random, state_transition_list, config) {
}

StateTransitionD::StateTransitionD(const StateTransitionD& orig) {
}

StateTransitionD::~StateTransitionD() {
}

NextState StateTransitionD::GetNextState(Person* person) const {
    return NextState(0, HostState::DEATH);
}