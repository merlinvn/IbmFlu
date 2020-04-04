/* 
 * File:   StateTransitionH.h
 * Author: merlin
 *
 * Created on May 16, 2012, 10:55 AM
 */

#ifndef STATETRANSITIONH_H
#define	STATETRANSITIONH_H

#include "StateTransition.h"

class StateTransitionH : public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionH)
public:
    StateTransitionH(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);

    virtual ~StateTransitionH();

    virtual NextState GetNextState(Person* person = NULL) const;
private:

};

#endif	/* STATETRANSITIONH_H */

