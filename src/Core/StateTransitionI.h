/* 
 * File:   StateTransitionFromI.h
 * Author: merlin
 *
 * Created on May 15, 2012, 3:24 PM
 */

#ifndef STATETRANSITIONFROMI_H
#define	STATETRANSITIONFROMI_H

#include "StateTransition.h"

class StateTransitionI : public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionI)

public:
    StateTransitionI(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    virtual ~StateTransitionI();

    //this function will return a pair value including duration will stay in the current state and the next state to move on
    virtual NextState GetNextState(Person* person = NULL) const;
private:

};

#endif	/* STATETRANSITIONFROMI_H */

