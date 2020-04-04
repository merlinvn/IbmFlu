/* 
 * File:   StateTransitionR.h
 * Author: merlin
 *
 * Created on May 20, 2012, 3:35 PM
 */

#ifndef STATETRANSITIONR_H
#define	STATETRANSITIONR_H
#include "StateTransition.h"

class StateTransitionR : public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionR);
public:
    
    StateTransitionR(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    
    virtual ~StateTransitionR();
    
    virtual NextState GetNextState(Person* person = NULL) const;
    
private:

};

#endif	/* STATETRANSITIONR_H */

