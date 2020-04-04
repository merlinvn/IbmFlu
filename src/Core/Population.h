/* 
 * File:   Population.h
 * Author: merlin
 *
 * Created on May 7, 2012, 2:39 PM
 */

#ifndef POPULATION_H
#define	POPULATION_H

#include <vector>
#include <list>
#include <string>

#include "Person.h"
#include "PropertyMacro.h"

#include "PersonIndex.h"
#include "PersonIndexAll.h"
#include "PersonIndexByLocationStateAgeClass.h"
#include "PersonIndexByLocationStateVirusStrainJK.h"
#include "Type.h"

class Model;
class Config;

class Population {
    DISALLOW_COPY_AND_ASSIGN_(Population)
    
    PersonIndexList indexList_;
    POINTER_PROPERTY(Model, model);

public:

    PersonIndexAll* personIndexAll;
    PersonIndexByLocationStateAgeClass* personIndexByLocationStateAgeClass;
    PersonIndexByLocationStateVirusStrainJK* personIndexByLocationStateVirusStrainJK;


public:
    Population(Model* model = NULL, const int& numberOfLocation = 1, const int& numberOfAgeClass = 7, const int& M = 10, const int& N = 40);

    virtual ~Population();

    void Initialize(Config* config);

    Person* at(const int& location, const HostState::HostStates& state, const int& age_class, const int& index);
    Person* at(const int& location, const HostState::HostStates& state, const int& j, const int& k, const int& index);

    virtual void AddPerson(Person* p);
    //Just remove pointer Person out of index, user must delete pointer manually
    virtual void RemovePerson(Person* p);


    virtual void NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue);

    virtual int size(const int& location = 0) const;
    virtual int size(const int& location, const HostState::HostStates& state, const int&j, const int& k) const;
    virtual int size(const int& location, const HostState::HostStates& state, const int& age_class) const;
    virtual int size(const int& location, const HostState::HostStates& state) const;

    Person* new_infect_individual(const int& location, const int& age_class, const int& infection_index, VirusStrain virusStrain, Person* infectedBy = NULL);

    void CleanUpIndividualsWithDeathState();

    int number_of_individuals_with_virus();
    
private:

};




#endif	/* POPULATION_H */

