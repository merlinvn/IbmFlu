/* 
 * File:   StateTransitionE.h
 * Author: merlin
 *
 * Created on May 16, 2012, 11:01 AM
 */

#ifndef STATETRANSITIONE_H
#define	STATETRANSITIONE_H

#include "StateTransition.h"


class StateTransitionE: public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionE);
    
public:
    StateTransitionE(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    
    virtual ~StateTransitionE();
    
    virtual NextState GetNextState(Person* person = NULL) const;
private:

};

#endif	/* STATETRANSITIONE_H */

