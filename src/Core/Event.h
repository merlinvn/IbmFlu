/* 
 * File:   Event.h
 * Author: merlin
 *
 * Created on May 7, 2012, 2:39 PM
 */

#ifndef EVENT_H
#define	EVENT_H
#include "ObjectPool.h"
#include "PropertyMacro.h"

class Person;
class Scheduler;

class Event { 
    DISALLOW_COPY_AND_ASSIGN_(Event);
    PROPERTY(int, event_time);
    POINTER_PROPERTY(Person, person);
    PROPERTY(bool, executable);
    POINTER_PROPERTY(Scheduler, scheduler);
    
public:
    
    Event(const int& time = 0, Person* person = NULL, const bool& executable = true, Scheduler* scheduler= NULL);    
    virtual ~Event();    
    virtual void Execute() = 0;
    
private:

};

#endif	/* EVENT_H */

