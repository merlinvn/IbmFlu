/* 
 * File:   PersonIndexAll.h
 * Author: merlin
 *
 * Created on May 8, 2012, 10:20 AM
 */

#ifndef PERSONINDEXALL_H
#define	PERSONINDEXALL_H

#include "PersonIndex.h"

class PersonIndexAll : public PersonIndex {
public:
    PersonVector vPerson;
public:
    PersonIndexAll();
    PersonIndexAll(const PersonIndexAll& orig);
    virtual ~PersonIndexAll();

    virtual void AddPerson(Person* p);
    virtual void RemovePerson(Person* p);
    virtual int total_size() const;
    
    virtual void NotifyChange(Person* p, const std::string& propertyName,const void* oldValue,const void* newValue  );
private:

};

#endif	/* PERSONINDEXALL_H */

