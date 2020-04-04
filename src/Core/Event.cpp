/* 
 * File:   Event.cpp
 * Author: merlin
 * 
 * Created on May 7, 2012, 2:39 PM
 */

#include "Event.h"
#include "Scheduler.h"
#include "Person.h"

Event::Event(const int& time, Person* person, const bool& executable, Scheduler* scheduler) : event_time_(time),
person_(person), executable_(executable), scheduler_(scheduler) {

}

Event::~Event() {    
    if(person_!=NULL)
    {        
        person_->RemoveEvent(this);        
    }
}

