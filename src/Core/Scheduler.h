/* 
 * File:   Scheduler.h
 * Author: merlin
 *
 * Created on May 9, 2012, 4:28 PM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "PropertyMacro.h"
#include <vector>
#include <list>
#include "Type.h"

class Model;

class Scheduler {
    DISALLOW_COPY_AND_ASSIGN_(Scheduler);
    PROPERTY(int, current_time);
    PROPERTY(int, total_time);

    PROPERTY(TimeEventList, event_list);
    POINTER_PROPERTY(Model, model);

    PROPERTY(ReporterList, end_of_day_reporters);
    
public:
    Scheduler(Model* model = NULL, const int& total_time = 400, const int& current_time = 0);
    
    virtual ~Scheduler();
    
    void Schedule(Event* event);
    void Cancel(Event* event);
    
    //This will loop through every time step and Run all event
    void Run();
    
    
    void BeginOfTimeStep();
    
    void EndOfTimeStep();
    
    void RegisterDailyReporter(Reporter* reporter);
    
    bool CanStop();
    
private:

};

#endif	/* SCHEDULER_H */

