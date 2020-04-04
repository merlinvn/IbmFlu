/* 
 * File:   PersonIndexByLocationStateAgeClass.cpp
 * Author: merlin
 * 
 * Created on May 8, 2012, 11:48 AM
 */

#include "PersonIndexByLocationStateAgeClass.h"

PersonIndexByLocationStateAgeClass::PersonIndexByLocationStateAgeClass(const int& numberOfLocation, const int& numberOfState, const int& numberOfAgeClass)
: vPerson(std::vector< std::vector < std::vector <PersonVector> > > (numberOfLocation,
std::vector < std::vector <PersonVector> > (numberOfState,
std::vector< PersonVector > (numberOfAgeClass, PersonVector())))) {

}

PersonIndexByLocationStateAgeClass::PersonIndexByLocationStateAgeClass(const PersonIndexByLocationStateAgeClass& orig) {

}

PersonIndexByLocationStateAgeClass::~PersonIndexByLocationStateAgeClass() {
    vPerson.clear();
}

void PersonIndexByLocationStateAgeClass::AddPerson(Person* p) {

    vPerson[p->location()][p->state()][p->age_class()].push_back(p);
    p->index_in_PersonIndexByLocation_State_AgeClass = vPerson[p->location()][p->state()][p->age_class()].size() - 1;
}

void PersonIndexByLocationStateAgeClass::RemovePerson(Person* p) {
    //move the last element to current position and remove the last holder          
    PersonVector pv = vPerson[p->location()][p->state()][p->age_class()];
    pv.back()->index_in_PersonIndexByLocation_State_AgeClass = p->index_in_PersonIndexByLocation_State_AgeClass;
    pv[p->index_in_PersonIndexByLocation_State_AgeClass] = pv.back();
    pv.pop_back();
    p->index_in_PersonIndexByLocation_State_AgeClass = -1;
}

int PersonIndexByLocationStateAgeClass::size(const int& location) const {
    //TODO:Test it later

    int result = 0;

    for (int state = 0; state < vPerson[location].size(); state++) {
        for (int age_class = 0; age_class < vPerson[location][state].size(); age_class++) {
            result += vPerson[location][state][age_class].size();
        }
    }

    return result;
}

int PersonIndexByLocationStateAgeClass::size(const int& location, const HostState::HostStates& state, const int& age_class) const {
    return vPerson[location][state][age_class].size();
}

int PersonIndexByLocationStateAgeClass::size(const int& location, const HostState::HostStates& state) const {
    int result = 0;
    for (int age_class = 0; age_class < vPerson[location][state].size(); age_class++) {
        result += vPerson[location][state][age_class].size();
    }
    return result;

}

int PersonIndexByLocationStateAgeClass::total_size() const {
    int result = 0;
    for (int location = 0; location < vPerson.size(); location++) {
        for (int state = 0; state < vPerson[location].size(); state++) {
            for (int age_class = 0; age_class < vPerson[location][state].size(); age_class++) {
                result += vPerson[location][state][age_class].size();
            }
        }
    }
    return result;
}

void PersonIndexByLocationStateAgeClass::NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue) {

    if (propertyName == "Location") {
        ChangeLocation(p, *(int*) oldValue, *(int*) newValue);
    } else if (propertyName == "State") {
        ChangeState(p, *(HostState::HostStates*) oldValue, *(HostState::HostStates*) newValue);
    } else if (propertyName == "Age") {
        ChangeAge(p, *(int*) oldValue, *(int*) newValue);
    }
}

void PersonIndexByLocationStateAgeClass::ChangeLocation(Person* p, const int& from, const int& to) {
    //remove from old location 
    vPerson[from][p->state()][p->age_class()].back()->index_in_PersonIndexByLocation_State_AgeClass = p->index_in_PersonIndexByLocation_State_AgeClass;
    vPerson[from][p->state()][p->age_class()][p->index_in_PersonIndexByLocation_State_AgeClass] = vPerson[from][p->state()][p->age_class()].back();
    vPerson[from][p->state()][p->age_class()].pop_back();

    //move to new location
    vPerson[to][p->state()][p->age_class()].push_back(p);
    p->index_in_PersonIndexByLocation_State_AgeClass = vPerson[to][p->state()][p->age_class()].size() - 1;

}

void PersonIndexByLocationStateAgeClass::ChangeState(Person* p, const HostState::HostStates& from, const HostState::HostStates& to) {
    //remove from old state
    vPerson[p->location()][from][p->age_class()].back()->index_in_PersonIndexByLocation_State_AgeClass = p->index_in_PersonIndexByLocation_State_AgeClass;
    vPerson[p->location()][from][p->age_class()][p->index_in_PersonIndexByLocation_State_AgeClass] = vPerson[p->location()][from][p->age_class()].back();
    vPerson[p->location()][from][p->age_class()].pop_back();

    //move to new state
    vPerson[p->location()][to][p->age_class()].push_back(p);
    p->index_in_PersonIndexByLocation_State_AgeClass = vPerson[p->location()][to][p->age_class()].size() - 1;
}

void PersonIndexByLocationStateAgeClass::ChangeAge(Person* p, const int& from, const int& to) {
    //remove from old age
    vPerson[p->location()][p->state()][from].back()->index_in_PersonIndexByLocation_State_AgeClass = p->index_in_PersonIndexByLocation_State_AgeClass;
    vPerson[p->location()][p->state()][from][p->index_in_PersonIndexByLocation_State_AgeClass] = vPerson[p->location()][p->state()][from].back();
    vPerson[p->location()][p->state()][from].pop_back();

    //move to new age
    vPerson[p->location()][p->state()][to].push_back(p);
    p->index_in_PersonIndexByLocation_State_AgeClass = vPerson[p->location()][p->state()][to].size() - 1;
}

Person* PersonIndexByLocationStateAgeClass::get(const int& location, const HostState::HostStates& state, const int& age_class, const int& index) {
    return vPerson[location][state][age_class][index];
}