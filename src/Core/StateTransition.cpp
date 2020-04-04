/* 
 * File:   StateTransition.cpp
 * Author: merlin
 * 
 * Created on May 10, 2012, 11:07 AM
 */

#include "StateTransition.h"
#include "Random.h"
#include "Person.h"


StateTransition::StateTransition( HostState::HostStates state, Random* random, StateTransitionPointerVector* state_transition_list, Config* config) :
 state_(state),random_(random),  state_transition_list_(state_transition_list), config_(config) {
}

StateTransition::~StateTransition() {
}



StateTransition* StateTransition::GetStateTranstiton(HostState::HostStates state) {
    if (state_transition_list_ == NULL)
        return NULL;
    return (*state_transition_list_)[state];
}

