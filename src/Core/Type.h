/* 
 * File:   Type.h
 * Author: merlin
 *
 * Created on May 22, 2012, 10:26 AM
 */

#ifndef TYPE_H
#define	TYPE_H

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include "HostState.h"

class Event;
class Reporter;
class Person;
class PersonIndex;

typedef std::list<Event*> EventList;
typedef EventList::iterator EventListIterator;
typedef std::vector<EventList> TimeEventList;
typedef TimeEventList::iterator TimeEventListIterator;
typedef std::list<Reporter*> ReporterList;

typedef std::vector<double> DoubleVector;
typedef DoubleVector::iterator DoubleVectorIterator;

typedef std::vector<DoubleVector> DoubleMatrix;

typedef std::vector<int> IntVector;

typedef std::pair<int, int> VirusStrain;

typedef std::vector<Event*> EventPointerVector;

typedef std::vector<VirusStrain> VirusStrainVector;
typedef VirusStrainVector::iterator VirusStrainVectorIterator;

typedef std::vector<Person*> PersonVector;
typedef PersonVector::iterator PersonVectorIterator;

typedef std::list<PersonIndex*> PersonIndexList;
typedef PersonIndexList::iterator PersonIndexListIterator;


typedef std::vector<HostState::HostStates> HostStateVector;
typedef HostStateVector::iterator HostStateVectorIterator;

typedef std::pair<int, HostState::HostStates> NextState;

typedef std::map<std::pair<int,int>,int> PairIntIntMap;
typedef std::map<std::pair<int,int>,int>::iterator PairIntIntMapIterator;



template <class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif	/* TYPE_H */

