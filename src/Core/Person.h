/* 
 * File:   Person.h
 * Author: merlin
 *
 * Created on May 7, 2012, 2:39 PM
 */

#ifndef PERSON_H
#define	PERSON_H

#include <string>

#include "ObjectPool.h"
#include "PropertyMacro.h"
#include "HostState.h"
#include "Type.h"

class Population;
class Virus;
class Model;
class Random;
class Event;

class Person {
    OBJECTPOOL(Person);

    DISALLOW_COPY_AND_ASSIGN_(Person);

    PROPERTY_HEADER(int, age_class);
    PROPERTY_HEADER(HostState::HostStates, state);
    PROPERTY_HEADER(int, location);

    POINTER_PROPERTY(Population, population);

    POINTER_PROPERTY_HEADER(Virus, current_virus);

    POINTER_PROPERTY(EventPointerVector, event_list);

    POINTER_PROPERTY(VirusStrainVector, today_infection_list)
    POINTER_PROPERTY(PersonVector, today_infection_source)

    POINTER_PROPERTY(PersonVector, infected_individuals)
    POINTER_PROPERTY(Person, infected_by)
    
    PROPERTY(VirusStrain, last_infected_strain)


    //location in the nested index 
public:
    int index_in_PersonIndexAll;
    int index_in_PersonIndexByLocation_State_AgeClass;
    int index_in_PersonIndexByLocation_State_VirusStrain;



public:

    Person(const int& age_class = 0, const HostState::HostStates& state = HostState::SUSCEPTIBLE,
            const int& location = 0, Population* population = NULL, EventPointerVector* event_list = NULL, VirusStrainVector* infection_list = NULL, PersonVector* infected_individuals = NULL, PersonVector* today_infection_source = NULL, Person* infected_by = NULL);
    virtual ~Person();

    virtual VirusStrain current_virus_strain() const;

    void resolve_infection_list(Model* config);

    void Infect(const VirusStrain& virusStrain);

    void mutate_virus(Random* random, const int& maxJ, const int& maxK);

    virtual void AddEvent(Event* event);
    virtual void RemoveEvent(Event* event);

    void ReleaseEvents();

private:
    virtual void NotifyChange(const std::string& propertyName, const void* oldValue, const void* newValue);
};

#endif	/* PERSON_H */

