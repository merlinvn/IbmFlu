/* 
 * File:   StateTransitionS.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 11:15 AM
 */

#include "StateTransitionS.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"

StateTransitionS::StateTransitionS(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::SUSCEPTIBLE, random, state_transition_list, config) {
}

StateTransitionS::StateTransitionS(const StateTransitionS& orig) {
}

StateTransitionS::~StateTransitionS() {
}

NextState StateTransitionS::GetNextState(Person* person) const {
    return NextState(0, HostState::EXPOSED);
}
