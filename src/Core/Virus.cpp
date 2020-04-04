/* 
 * File:   Virus.cpp
 * Author: merlin
 * 
 * Created on May 7, 2012, 6:32 PM
 */

#include "Virus.h"

ObjectPool<Virus>* Virus::object_pool = NULL;


Virus::Virus(VirusStrain strain): strain_(strain) {
}

Virus::Virus(const Virus& orig) {
}

Virus::~Virus() {
}

