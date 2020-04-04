/* 
 * File:   Person.cpp
 * Author: merlin
 * 
 * Created on May 7, 2012, 2:39 PM
 */

#include "Person.h"
#include "Population.h"
#include "Virus.h"
#include "Config.h"
#include "Event.h"
#include "Model.h"
#include "Random.h"
#include "Event.h"

ObjectPool<Person>* Person::object_pool = NULL;

Person::Person(const int & age_class, const HostState::HostStates& state, const int& location, Population* population, EventPointerVector* event_list, VirusStrainVector* infection_list, PersonVector* infected_individuals, PersonVector* today_infection_source, Person* infected_by)
: age_class_(age_class), state_(state), location_(location), population_(population), current_virus_(NULL), event_list_(event_list), today_infection_list_(infection_list), infected_individuals_(infected_individuals), today_infection_source_(today_infection_source), infected_by_(infected_by) {

}

Person::~Person() {
    if (current_virus_ != NULL) {
        delete current_virus_;
        current_virus_ = NULL;
    }

    //unschedule event in this list by set executable to false
    //the scheduler will attual delete it
    if (event_list_ != NULL) {
        ReleaseEvents();
        event_list_->clear();
        delete event_list_;
        event_list_ = NULL;
    }

    if (today_infection_list_ != NULL) {
        delete today_infection_list_;
        today_infection_list_ = NULL;
    }

    if (infected_individuals_ != NULL) {
        delete infected_individuals_;
        infected_individuals_ = NULL;
    }

    if (today_infection_source_ != NULL) {
        delete today_infection_source_;
        today_infection_source_ = NULL;
    }
    infected_by_ = NULL;

}

int Person::age_class() const {
    return age_class_;
}

void Person::set_age_class(int value) {
    if (value != age_class_) {
        NotifyChange("Age", &age_class_, &value);
        age_class_ = value;
    }
}

HostState::HostStates Person::state() const {
    return state_;
}

void Person::set_state(HostState::HostStates value) {
    if (value != state_) {

        NotifyChange("State", &state_, &value);
        state_ = value;

        // if change state to DEATH or Recover then automatically remove virus
        if (value == HostState::DEATH || value == HostState::RECOVERED || value == HostState::SUSCEPTIBLE) {
            //remove Virus
            set_current_virus(NULL);
        }
    }
}

int Person::location() const {
    return location_;
}

void Person::set_location(int value) {
    if (value != location_) {
        NotifyChange("Location", &location_, &value);
        location_ = value;
    }
}

void Person::NotifyChange(const std::string& propertyName, const void* oldValue, const void* newValue) {
    if (population_ != NULL)
        population_->NotifyChange(this, propertyName, oldValue, newValue);
}

Virus* Person::current_virus() const {
    return current_virus_;
}

void Person::set_current_virus(Virus* virus) {
    if (virus != current_virus_) {
        NotifyChange("Virus", current_virus_, virus);
        //delete old virus
        if (current_virus_ != NULL) {
            last_infected_strain_ = current_virus_->strain();
            delete current_virus_;
        }

        current_virus_ = virus;
    }
}

VirusStrain Person::current_virus_strain() const {
    if (current_virus_ != NULL) {
        return current_virus_->strain();
    }
    return VirusStrain(-1, -1);
}

void Person::resolve_infection_list(Model* model) {
    //TODO: review mechanism of select 1 virus strain in multiple list

    // select virus strain base on k paramenters;
    std::vector<double> kVector;
    double totalK = 0;
    for (VirusStrainVectorIterator it = today_infection_list_->begin(); it != today_infection_list_->end(); it++) {
        kVector.push_back((*it).second);
        totalK += (*it).second;
    }
    double s = 0;
    for (int i = 0; i < kVector.size(); i++) {
        s += kVector[i];
        kVector[i] = s / totalK;
    }

    double dist = model->random()->RandomUniform();

    int i = 0;
    while (dist > kVector[i] && i < kVector.size()) {
        i += 1;
    }

    VirusStrain selectedVirusStrain = (*today_infection_list_)[i];
    infected_by_ = (*today_infection_source_)[i];
    infected_by_->infected_individuals()->push_back(this);

    Infect(selectedVirusStrain);
    today_infection_source_->clear();
    today_infection_list_->clear();
}

void Person::Infect(const VirusStrain& virusStrain) {
    //real infection
    Virus* virus = new Virus(virusStrain);
    set_current_virus(virus);
}

void Person::mutate_virus(Random* random, const int& maxJ, const int& maxK) {
    int j = current_virus_strain().first;
    int k = current_virus_strain().second;

    //select j or k to mutate
    double selectJK = random->RandomUniform();
    if (selectJK < 0.5) {
        //select j
        if (j == 0) {
            if (selectJK < 0.25) {
                j += 1;
            }
        } else if (j == maxJ) {
            if (selectJK < 0.25) {
                j -= 1;
            }
        } else {
            double plusOrMinus = random->RandomUniform();
            if (plusOrMinus < 0.5) {
                //plus 
                j += 1;
            } else {
                //minus
                j -= 1;
            }
        }
    } else {
        //select k
        if (k == 0) {
            if (selectJK < 0.75) {
                k += 1;
            }

        } else if (k == maxK) {
            if (selectJK < 0.75) {
                k -= 1;
            }
        } else {
            double plusOrMinus = random->RandomUniform();
            if (plusOrMinus < 0.5) {
                //plus 
                k += 1;
            } else {
                //minus
                k -= 1;
            }
        }
    }
    //    std::cout << "Mutation from " << "(" << current_virus_strain().first << "," << current_virus_strain().second << ")" << " to " << "(" << j << "," << k << ")" << std::endl;
    //new virus strain defined in j and k
    Virus* virus = new Virus(VirusStrain(j, k));
    //set current virus to new virus
    set_current_virus(virus);

}

void Person::AddEvent(Event* event) {
    if (event_list_ == NULL)return;
    event_list_->push_back(event);
}

//this function will called by delete event in the scheduler

void Person::RemoveEvent(Event* event) {
    if (event_list_ == NULL)return;
    for (int i = 0; i < event_list_->size(); i++) {
        if ((*event_list_)[i] == event) {

            (*event_list_)[i] = event_list_->back();
            event_list_->pop_back();
            return;
        }
    }
}

void Person::ReleaseEvents() {
    if (event_list_ == NULL)return;
    for (int i = 0; i < event_list_->size(); i++) {
        (*event_list_)[i]->set_executable(false);
        (*event_list_)[i]->set_person(NULL);

    }
}