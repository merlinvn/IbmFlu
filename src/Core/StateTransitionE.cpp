/* 
 * File:   StateTransitionE.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 11:01 AM
 */
#include <math.h>

#include "StateTransitionE.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"

StateTransitionE::StateTransitionE(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::EXPOSED, random, state_transition_list, config) {
}

StateTransitionE::StateTransitionE(const StateTransitionE& orig) {
}

StateTransitionE::~StateTransitionE() {
}

NextState StateTransitionE::GetNextState(Person* person) const {
    int time_e_to_i = round ( random()-> RandomGamma(config()->gamma_coeff_time_E_to_I(), config()->coeff_EtoI()));   
    return NextState(time_e_to_i, HostState::INFECTIOUS);
}