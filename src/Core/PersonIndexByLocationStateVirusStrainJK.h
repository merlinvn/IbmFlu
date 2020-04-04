/* 
 * File:   PersonIndexByLocationStateVirusStrainJK.h
 * Author: merlin
 *
 * Created on May 16, 2012, 3:12 PM
 */

#ifndef PERSONINDEXBYLOCATIONSTATEVIRUSSTRAINJK_H
#define	PERSONINDEXBYLOCATIONSTATEVIRUSSTRAINJK_H

#include "PersonIndex.h"
#include "PropertyMacro.h"
#include "Person.h"

class PersonIndexByLocationStateVirusStrainJK : public PersonIndex {
    DISALLOW_COPY_AND_ASSIGN_(PersonIndexByLocationStateVirusStrainJK);

public:
    std::vector< std::vector < std::vector <std::vector<PersonVector> > > > vPerson;

public:
    PersonIndexByLocationStateVirusStrainJK(const int& number_of_locations =1, const int& numberOfState = HostState::NUMBER, const int& M=10, const int& N=40);
    virtual ~PersonIndexByLocationStateVirusStrainJK();


    virtual void AddPerson(Person* p);
    virtual void RemovePerson(Person* p);
    virtual int total_size() const;
    
    virtual int size(const int& location, const HostState::HostStates& state, const int&j , const int& k) const;

    virtual void NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue);

private:
    void ChangeLocation(Person*p, const int& from, const int& to);
    void ChangeState(Person*p, const HostState::HostStates& from, const HostState::HostStates& to);
    void ChangeVirus(Person*p, Virus* from, Virus* to);



};

#endif	/* PERSONINDEXBYLOCATIONSTATEVIRUSSTRAINJK_H */

