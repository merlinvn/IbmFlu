/* 
 * File:   PersonIndex.h
 * Author: merlin
 *
 * Created on May 8, 2012, 10:04 AM
 */

#ifndef PERSONINDEX_H
#define	PERSONINDEX_H

#include <vector>
#include <iostream>
#include "Type.h"

class Person;


class PersonIndex {
public:
    PersonIndex();
    PersonIndex(const PersonIndex& orig);
    virtual ~PersonIndex();

    virtual void AddPerson(Person* p) = 0;
    virtual void RemovePerson(Person* p) = 0;
    virtual int total_size() const = 0;

    virtual void NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue) = 0;

private:

};




#endif	/* PERSONINDEX_H */

