/* 
 * File:   ChangeStateEvent.h
 * Author: merlin
 *
 * Created on May 10, 2012, 1:34 PM
 */

#ifndef CHANGESTATEEVENT_H
#define	CHANGESTATEEVENT_H

#include "Event.h"
#include "ObjectPool.h"
#include "PropertyMacro.h"

class StateTransition;

class ChangeStateEvent : public Event {
    OBJECTPOOL(ChangeStateEvent);
    DISALLOW_COPY_AND_ASSIGN_(ChangeStateEvent);
    POINTER_PROPERTY(StateTransition, state_transition);

public:

    explicit ChangeStateEvent(const int& time = 0, Person* person = nullptr, const bool& executable = true,
            Scheduler* scheduler = nullptr, StateTransition* stateTransition = nullptr);

    ~ChangeStateEvent() override;

    void Execute() override;
private:

};

#endif	/* CHANGESTATEEVENT_H */

