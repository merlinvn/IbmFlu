/* 
 * File:   StateTransitionQ.h
 * Author: merlin
 *
 * Created on May 16, 2012, 10:42 AM
 */

#ifndef STATETRANSITIONQ_H
#define	STATETRANSITIONQ_H

#include "StateTransition.h"

class StateTransitionQ: public StateTransition {
    DISALLOW_COPY_AND_ASSIGN_(StateTransitionQ)
    
public:
    StateTransitionQ(Random* random = NULL, StateTransitionPointerVector* state_transition_list = NULL, Config* config = NULL);

    virtual ~StateTransitionQ();
    
        //this function will return a pair value including duration will stay in the current state and the next state to move on
    virtual NextState GetNextState(Person* person = NULL) const;

    
private:

};

#endif	/* STATETRANSITIONQ_H */

