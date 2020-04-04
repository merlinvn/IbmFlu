/* 
 * File:   StateTransitionD.h
 * Author: merlin
 *
 * Created on May 16, 2012, 12:51 PM
 */

#ifndef STATETRANSITIOND_H
#define	STATETRANSITIOND_H

#include "StateTransition.h"


class StateTransitionD: public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionD);
    
public:
    StateTransitionD(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    
    virtual ~StateTransitionD();
    
    virtual NextState GetNextState(Person* person = NULL) const;
private:

};

#endif	/* STATETRANSITIOND_H */

