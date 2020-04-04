/* 
 * File:   Scheduler.cpp
 * Author: merlin
 * 
 * Created on May 9, 2012, 4:28 PM
 */

#include "Scheduler.h"
#include "Event.h"
#include "Model.h"
#include "Reporter.h"
#include "Config.h"
#include "Person.h"
#include "ChangeStateEvent.h"
#include "Population.h"

Scheduler::Scheduler(Model* model, const int& total_time, const int& current_time) : model_(model), total_time_(total_time), current_time_(current_time),
event_list_(total_time, EventList()) {

}

Scheduler::~Scheduler() {
    //Delete all event in the event list
    //Loop through each time step
    for (TimeEventListIterator eventListIt = event_list_.begin(); eventListIt != event_list_.end(); eventListIt++) {
        //loop through each event in each time
        for (EventListIterator eventIt = (*eventListIt).begin(); eventIt != (*eventListIt).end(); eventIt++) {
            //Destructor of Event will handle remove other related Link to event
            delete (*eventIt);
        }
    }

    //release reporter
    //    for (ReporterList::iterator it = end_of_day_reporters_.begin(); it != end_of_day_reporters_.end(); it++) {
    //        delete (*it);
    //    }
}

void Scheduler::Schedule(Event* event) {
    event_list_[event->event_time()].push_back(event);
    event->set_scheduler(this);

}

void Scheduler::Cancel(Event* event) {
    event->set_executable(false);
}

void Scheduler::Run() {
    //Loop through each time step
    int total = total_time_;
    if (model_ != NULL) {
        total = model_->config()->total_time();
    }

    for (current_time_ = 0; !CanStop(); current_time_++) {
        BeginOfTimeStep();

        //loop through each event in each time
        for (EventListIterator eventIt = event_list_[current_time_].begin(); eventIt != event_list_[current_time_].end(); eventIt++) {
            //Execute Event will handle remove other related Link to event
            Event* event = (*eventIt);
            if (event->executable()) {
                event->Execute();
            }

            if (event->person() != NULL) {
                event->person()->RemoveEvent(event);
                event->set_person(NULL);
            }
            delete(*eventIt);
        }
        event_list_[current_time_].clear();

        EndOfTimeStep();
        //EndOfDay: mutation Event, clean up Dead if necessary
    }
}

void Scheduler::BeginOfTimeStep() {
    if (model_ != NULL) {
        model_->PerformInfectionEvents();

        if (model_->TotalNumberOfCases() >= 1000 && model_->CaseFatalityAt1000Cases() == 0) {
            model_->set_CaseFatalityAt1000Cases(model_->CalculateAverageCaseFatality());
        }

        if (model_->config()->sd_trigger_at() > 0 && model_->TotalNumberOfCases() >= model_->config()->sd_trigger_at() && model_->social_distance_start_at() == -1) {
            //trigger Social distance            
            model_->set_reducing_factor(1 - model_->config()->sd_reducing_by());
            model_->set_social_distance_start_at(current_time_);
        }

        //relaxing
        if (model_->config()->sd_relaxing_in() > 0 && model_->social_distance_start_at() != -1 && (model_->social_distance_start_at() + model_->config()->sd_relaxing_in()) == current_time_) {
            model_->set_reducing_factor(1);
        }

    }
}

void Scheduler::EndOfTimeStep() {
    if (model_ != NULL) {
        model_->PerformMutationEvents();

        //report here
        for (ReporterList::iterator it = end_of_day_reporters_.begin(); it != end_of_day_reporters_.end(); it++) {
            (*it)->DailyReport(model_);
        }

        model_->CleanUpIndividualsWithDeathState();
    }
}

void Scheduler::RegisterDailyReporter(Reporter* reporter) {
    end_of_day_reporters_.push_back(reporter);
}

bool Scheduler::CanStop() {
    if (model_->population()->number_of_individuals_with_virus() == 0) {
        return true;
    }

    if (current_time_ >= total_time_ - 100) {
        //increase total time by 500 days
        for (int i = 0; i < 500; i++) {
            event_list_.push_back(EventList());
        }
        total_time_ += 500;
    }

    return false;
}