/* 
 * File:   StateTransitionS.h
 * Author: merlin
 *
 * Created on May 16, 2012, 11:15 AM
 */

#ifndef STATETRANSITIONS_H
#define	STATETRANSITIONS_H

#include "StateTransition.h"


class StateTransitionS: public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionS);
    
public:
    StateTransitionS(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);
    
    virtual ~StateTransitionS();
    
    //This function will never call
    virtual NextState GetNextState(Person* person = NULL) const;
    
private:

};

#endif	/* STATETRANSITIONS_H */

