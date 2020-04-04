/* 
 * File:   StateTransition.h
 * Author: merlin
 *
 * Created on May 10, 2012, 11:07 AM
 */

#ifndef STATETRANSITION_H
#define	STATETRANSITION_H

#include "PropertyMacro.h"
#include "HostState.h"

#include <vector>
#include "Type.h"

class Random;
class Person;
class Config;

class StateTransition {
public:
    typedef std::vector<StateTransition*> StateTransitionPointerVector;

    DISALLOW_COPY_AND_ASSIGN_(StateTransition)

    PROPERTY(HostState::HostStates, state);

    POINTER_PROPERTY(StateTransitionPointerVector, state_transition_list);

    POINTER_PROPERTY(Random, random);
    POINTER_PROPERTY(Config, config);

public:

    StateTransition(HostState::HostStates state = HostState::SUSCEPTIBLE, Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    virtual ~StateTransition();

    //this function will return a pair value including duration will stay in the current state and the next state to move on
    virtual NextState GetNextState(Person* person = NULL) const = 0;
    virtual StateTransition* GetStateTranstiton(HostState::HostStates state);

private:

};

#endif	/* STATETRANSITION_H */

