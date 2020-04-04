/* 
 * File:   PersonIndexAll.cpp
 * Author: merlin
 * 
 * Created on May 8, 2012, 10:20 AM
 */

#include "PersonIndexAll.h"
#include "Person.h"

PersonIndexAll::PersonIndexAll() {
}

PersonIndexAll::PersonIndexAll(const PersonIndexAll& orig) {
}

PersonIndexAll::~PersonIndexAll() {
    for (PersonVectorIterator it = vPerson.begin(); it != vPerson.end(); it++) {
        delete (*it);
    }
    vPerson.clear();
}

int PersonIndexAll::total_size() const {
    return vPerson.size();
}

void PersonIndexAll::AddPerson(Person* p) {
    vPerson.push_back(p);
    p->index_in_PersonIndexAll = vPerson.size() - 1;
}

void PersonIndexAll::RemovePerson(Person* p) {
    //move the last element to current position and remove the last holder          
    vPerson.back()->index_in_PersonIndexAll = p->index_in_PersonIndexAll;
    vPerson[p->index_in_PersonIndexAll] = vPerson.back();
    vPerson.pop_back();
    p->index_in_PersonIndexAll = -1;
}

void PersonIndexAll::NotifyChange(Person* p, const std::string& propertyName, const void* oldValue,const void* newValue)
{
    //this won't do anything 
}