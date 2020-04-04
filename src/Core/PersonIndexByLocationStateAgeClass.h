/* 
 * File:   PersonIndexByLocationStateAgeClass.h
 * Author: merlin
 *
 * Created on May 8, 2012, 11:48 AM
 */

#ifndef PERSONINDEXBYLOCATIONSTATEAGECLASS_H
#define	PERSONINDEXBYLOCATIONSTATEAGECLASS_H

#include "PersonIndex.h"
#include "Person.h"

class PersonIndexByLocationStateAgeClass : public PersonIndex {
    DISALLOW_COPY_AND_ASSIGN_(PersonIndexByLocationStateAgeClass);
    
public:
    std::vector< std::vector < std::vector <PersonVector> > > vPerson;

public:

    PersonIndexByLocationStateAgeClass(const int& numberOfLocation = 1, const int& numberOfState = HostState::NUMBER, const int& numberOfAgeClass = 1);    
    virtual ~PersonIndexByLocationStateAgeClass();

    virtual void AddPerson(Person* p);
    virtual void RemovePerson(Person* p);
    virtual int size(const int& location = 0) const;
    virtual int size(const int& location, const HostState::HostStates& state, const int& age_class) const;
    virtual int size(const int& location, const HostState::HostStates& state) const;
    
    virtual int total_size() const;

    virtual void NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue);
    
    Person* get(const int& location, const HostState::HostStates& state, const int& age_class, const int& index);

private:
    void ChangeLocation(Person*p, const int& from, const int& to);
    void ChangeAge(Person*p, const int& from, const int& to);
    void ChangeState(Person*p, const HostState::HostStates& from, const HostState::HostStates& to);
    
private:

};

#endif	/* PERSONINDEXBYLOCATIONSTATEAGECLASS_H */

