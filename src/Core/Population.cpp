/* 
 * File:   Population.cpp
 * Author: merlin
 * 
 * Created on May 7, 2012, 2:39 PM
 */

#include <algorithm>
#include "Population.h"
#include "PersonIndexAll.h"
#include "Model.h"
#include "Config.h"

Population::Population(Model* model, const int& numberOfLocation, const int& numberOfAgeClass, const int& M, const int& N) : model_(model), personIndexAll(new PersonIndexAll()),
personIndexByLocationStateAgeClass(new PersonIndexByLocationStateAgeClass(numberOfLocation, HostState::NUMBER, numberOfAgeClass)), personIndexByLocationStateVirusStrainJK(new PersonIndexByLocationStateVirusStrainJK(numberOfLocation, HostState::NUMBER, M, N)) {

    indexList_.push_back(personIndexAll);
    indexList_.push_back(personIndexByLocationStateAgeClass);
    indexList_.push_back(personIndexByLocationStateVirusStrainJK);
}

Population::~Population() {
    delete personIndexByLocationStateVirusStrainJK;
    delete personIndexByLocationStateAgeClass;
    //only PersonIndexAll release All Person in destructor other Index do not do anything
    //so call delete on it at last
    delete personIndexAll;
    indexList_.clear();
}

void Population::Initialize(Config* config) {
    //TODO::multiple location later

    //create population based on config in the model
    for (int loc = 0; loc < config->number_of_locations(); loc++) {
        int populationSize = config->population_size()[loc];
        int sum = 0;
        for (int age = 0; age < config->age_distribution().size(); age++) {
            int numberOfIndividuals = 0;

            if (age == config->age_distribution().size() - 1) {
                numberOfIndividuals = populationSize - sum;

            } else {
                numberOfIndividuals = populationSize * config->age_distribution()[age];
            }


            sum += numberOfIndividuals;
            for (int i = 0; i < numberOfIndividuals; i++) {
                //create new Person and add it
                Person* p = new Person(age, HostState::SUSCEPTIBLE, loc, this, new EventPointerVector(), new VirusStrainVector(), new PersonVector(), new PersonVector());
                AddPerson(p);
            }
        }
    }
}

void Population::AddPerson(Person* p) {
    for (PersonIndexListIterator it = indexList_.begin(); it != indexList_.end(); it++) {
        (*it)->AddPerson(p);
    }
    
    p->set_population(this);
}

void Population::RemovePerson(Person* p) {
    for (PersonIndexListIterator it = indexList_.begin(); it != indexList_.end(); it++) {
        (*it)->RemovePerson(p);
    }    
    //    delete p;
}

void Population::NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue) {
    //update index base on change
    for (PersonIndexListIterator it = indexList_.begin(); it != indexList_.end(); it++) {
        (*it)->NotifyChange(p, propertyName, oldValue, newValue);
    }
}

int Population::size(const int& location) const {
    return personIndexByLocationStateAgeClass->size(location);
}

int Population::size(const int& location, const HostState::HostStates& state, const int& j, const int& k) const {
    return personIndexByLocationStateVirusStrainJK->size(location, state, j, k);
}

int Population::size(const int& location, const HostState::HostStates& state, const int& age_class) const {
    return personIndexByLocationStateAgeClass->size(location, state, age_class);
}

int Population::size(const int& location, const HostState::HostStates& state) const {
    return personIndexByLocationStateAgeClass->size(location, state);
}

Person* Population::new_infect_individual(const int& location, const int& age_class, const int& infection_index, VirusStrain virusStrain, Person* infected_by) {
    Person* p = personIndexByLocationStateAgeClass->get(location, HostState::SUSCEPTIBLE, age_class, infection_index);
    //add VirusStrain to today infection list
    p->today_infection_list()->push_back(virusStrain);
    p->today_infection_source()->push_back(infected_by);
    return p;
}

void Population::CleanUpIndividualsWithDeathState() {
    HostState::HostStates state = HostState::DEATH;
    for (int location = 0; location < personIndexByLocationStateAgeClass->vPerson.size(); location++) {
        for (int age_class = 0; age_class < personIndexByLocationStateAgeClass->vPerson[location][state].size(); age_class++) {
            for (int index = 0; index < personIndexByLocationStateAgeClass->vPerson[location][state][age_class].size(); index++) {
                Person* p = personIndexByLocationStateAgeClass->vPerson[location][state][age_class][index];
                //remove from other index                
                personIndexByLocationStateVirusStrainJK->RemovePerson(p);
                personIndexAll->RemovePerson(p);
                //release memory
                delete p;
            }
            personIndexByLocationStateAgeClass->vPerson[location][state][age_class].clear();
        }
    }
}

Person* Population::at(const int& location, const HostState::HostStates& state, const int& age_class, const int& index) {
    return personIndexByLocationStateAgeClass->vPerson[location][state][age_class][index];
}

Person* Population::at(const int& location, const HostState::HostStates& state, const int& j, const int& k, const int& index) {
    return personIndexByLocationStateVirusStrainJK->vPerson[location][state][j][k][index];
}

int Population::number_of_individuals_with_virus() {

    int result = 0;
    for (int location = 0; location < model_->config()->number_of_locations(); location++) {
        for (int state = HostState::EXPOSED; state <= HostState::HOSPITALIZED; state++) {
            for (int age_class = 0; age_class < model_->config()->number_of_age_classes(); age_class++) {
                result += size(location, (HostState::HostStates)state, age_class);
            }
        }
    }
    return result;
}