/* 
 * File:   ChangeStateEvent.cpp
 * Author: merlin
 * 
 * Created on May 10, 2012, 1:34 PM
 */

#include <cassert>

#include "ChangeStateEvent.h"
#include "StateTransition.h"
#include "Person.h"
#include "Scheduler.h"

ObjectPool<ChangeStateEvent>* ChangeStateEvent::object_pool = nullptr;

ChangeStateEvent::ChangeStateEvent(const int &time, Person* person, const bool &executable,
                                   Scheduler* scheduler, StateTransition* stateTransition)
  : Event(time, person, executable, scheduler), state_transition_(stateTransition) {

}

ChangeStateEvent::~ChangeStateEvent() {
  state_transition_ = nullptr;
}

void ChangeStateEvent::Execute() {
//    assert(state_transition_->state_transition_list()->size() == 8);
  person()->set_state(state_transition_->state());

  if (state_transition_->state() == HostState::DEATH || state_transition_->state() == HostState::RECOVERED ||
      state_transition_->state() == HostState::SUSCEPTIBLE) {
    //will do nothing here
    set_executable(false);
    return;
  }

  NextState nextState = state_transition_->GetNextState(person());

  if (nextState.second < HostState::NUMBER) {

    StateTransition* nextStateTransition = state_transition_->GetStateTranstiton(nextState.second);

    auto* event = new ChangeStateEvent(event_time() + nextState.first, person(), true, scheduler(),
                                       nextStateTransition);
    scheduler()->Schedule(event);

  }
  //after Execute disable this
  set_executable(false);
}

