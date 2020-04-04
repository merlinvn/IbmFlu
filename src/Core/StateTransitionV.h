/* 
 * File:   StateTransitionV.h
 * Author: merlin
 *
 * Created on May 16, 2012, 10:51 AM
 */

#ifndef STATETRANSITIONV_H
#define	STATETRANSITIONV_H

#include "StateTransition.h"

class StateTransitionV: public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionV)
public:
    StateTransitionV(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    
    virtual ~StateTransitionV();
    
    virtual NextState GetNextState(Person* person = NULL) const;
private:

};

#endif	/* STATETRANSITIONV_H */

