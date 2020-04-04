/* 
 * File:   PersonIndexByLocationStateVirusStrainJK.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 3:12 PM
 */

#include "PersonIndexByLocationStateVirusStrainJK.h"
#include "Virus.h"

PersonIndexByLocationStateVirusStrainJK::PersonIndexByLocationStateVirusStrainJK(const int& number_of_locations, const int& numberOfState, const int& M, const int& N) :
vPerson(std::vector< std::vector < std::vector < std::vector <PersonVector> > > > (number_of_locations,
std::vector < std::vector < std::vector <PersonVector> > > (numberOfState,
std::vector< std::vector<PersonVector > > (M,
std::vector<PersonVector>(N, PersonVector()))))) {


    vPerson = std::vector< std::vector < std::vector < std::vector <PersonVector> > > > (number_of_locations,
            std::vector < std::vector < std::vector <PersonVector> > > (numberOfState,
            std::vector< std::vector<PersonVector > > (M,
            std::vector<PersonVector > (N, PersonVector()))));
}

PersonIndexByLocationStateVirusStrainJK::PersonIndexByLocationStateVirusStrainJK(const PersonIndexByLocationStateVirusStrainJK& orig) {
}

PersonIndexByLocationStateVirusStrainJK::~PersonIndexByLocationStateVirusStrainJK() {
}

void PersonIndexByLocationStateVirusStrainJK::AddPerson(Person* p) {
    if (p->current_virus() == NULL) {
        //don't do anything
        return;
    }

    VirusStrain vr = p->current_virus_strain();
    int to_j = vr.first;
    int to_k = vr.second;
    vPerson[p->location()][p->state()][to_j][to_k].push_back(p);
    p->index_in_PersonIndexByLocation_State_VirusStrain = vPerson[p->location()][p->state()][to_j][to_k].size() - 1;

}

void PersonIndexByLocationStateVirusStrainJK::RemovePerson(Person* p) {

    if (p->current_virus() == NULL) {
        //don't do anything
        return;
    }
    
    VirusStrain vr = p->current_virus_strain();
    int to_j = vr.first;
    int to_k = vr.second;
    vPerson[p->location()][p->state()][to_j][to_k][p->index_in_PersonIndexByLocation_State_VirusStrain] = vPerson[p->location()][p->state()][to_j][to_k].back();
    vPerson[p->location()][p->state()][to_j][to_k].pop_back();
    p->index_in_PersonIndexByLocation_State_VirusStrain = -1;

}

int PersonIndexByLocationStateVirusStrainJK::total_size() const {
    int result = 0;
    for (int loc = 0; loc < vPerson.size(); loc++) {
        for (int state = 0; state < vPerson[loc].size(); state++) {
            for (int j = 0; j < vPerson[loc][state].size(); j++) {
                for (int k = 0; k < vPerson[loc][state][j].size(); k++) {
                    result += vPerson[loc][state][j][k].size();
                }
            }
        }
    }
    return result;
}

int PersonIndexByLocationStateVirusStrainJK::size(const int& location, const HostState::HostStates& state, const int& j, const int& k) const {
    return vPerson[location][state][j][k].size();
}

void PersonIndexByLocationStateVirusStrainJK::NotifyChange(Person* p, const std::string& propertyName, const void* oldValue, const void* newValue) {
    if (propertyName == "Location") {
        ChangeLocation(p, *(int*) oldValue, *(int*) newValue);
    } else if (propertyName == "State") {
        ChangeState(p, *(HostState::HostStates*) oldValue, *(HostState::HostStates*) newValue);
    } else if (propertyName == "Virus") {
        ChangeVirus(p, (Virus*) oldValue, (Virus*) newValue);
    }
}

void PersonIndexByLocationStateVirusStrainJK::ChangeLocation(Person* p, const int& from, const int& to) {
    if (p->current_virus_strain() == VirusStrain(-1, -1)) {
        //don't do anything
        return;
    }

    int j = p->current_virus_strain().first;
    int k = p->current_virus_strain().second;

    vPerson[from][p->state()][j][k].back()->index_in_PersonIndexByLocation_State_VirusStrain = p->index_in_PersonIndexByLocation_State_VirusStrain;
    vPerson[from][p->state()][j][k][p->index_in_PersonIndexByLocation_State_VirusStrain] = vPerson[from][p->state()][j][k].back();
    vPerson[from][p->state()][j][k].pop_back();

    //move to new location
    vPerson[to][p->state()][j][k].push_back(p);
    p->index_in_PersonIndexByLocation_State_VirusStrain = vPerson[to][p->state()][j][k].size() - 1;
}

void PersonIndexByLocationStateVirusStrainJK::ChangeState(Person* p, const HostState::HostStates& from, const HostState::HostStates& to) {
    if (p->current_virus_strain() == VirusStrain(-1, -1)) {
        //don't do anything
        return;
    }

    int j = p->current_virus_strain().first;
    int k = p->current_virus_strain().second;

    //remove from old state
    vPerson[p->location()][from][j][k].back()->index_in_PersonIndexByLocation_State_VirusStrain = p->index_in_PersonIndexByLocation_State_VirusStrain;
    vPerson[p->location()][from][j][k][p->index_in_PersonIndexByLocation_State_VirusStrain] = vPerson[p->location()][from][j][k].back();
    vPerson[p->location()][from][j][k].pop_back();

    //move to new state
    vPerson[p->location()][to][j][k].push_back(p);
    p->index_in_PersonIndexByLocation_State_VirusStrain = vPerson[p->location()][to][j][k].size() - 1;


}

void PersonIndexByLocationStateVirusStrainJK::ChangeVirus(Person* p, Virus* from, Virus* to) {
    if (p->current_virus() == NULL) {
        //not exist in the index        
        //add it        
        int to_j = to->strain() .first;
        int to_k = to->strain().second;
        
        vPerson[p->location()][p->state()][to_j][to_k].push_back(p);
        p->index_in_PersonIndexByLocation_State_VirusStrain = vPerson[p->location()][p->state()][to_j][to_k].size() - 1;
        return;
    }

    if (to == NULL) {
        //remove from index
        RemovePerson(p);
        return;
    }

    //only update index if strain is different
    if (from->strain() != to->strain()) {
        int from_j = from->strain().first;
        int from_k = from->strain().second;

        int to_j = to->strain().first;
        int to_k = to->strain().second;

        //remove from old strain
        vPerson[p->location()][p->state()][from_j][from_k].back()->index_in_PersonIndexByLocation_State_VirusStrain = p->index_in_PersonIndexByLocation_State_VirusStrain;
        vPerson[p->location()][p->state()][from_j][from_k][p->index_in_PersonIndexByLocation_State_VirusStrain] = vPerson[p->location()][p->state()][from_j][from_k].back();
        vPerson[p->location()][p->state()][from_j][from_k].pop_back();

        //move to new strain
        vPerson[p->location()][p->state()][to_j][to_k].push_back(p);
        p->index_in_PersonIndexByLocation_State_VirusStrain = vPerson[p->location()][p->state()][to_j][to_k].size() - 1;

    }
}


