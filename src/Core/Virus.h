/* 
 * File:   Virus.h
 * Author: merlin
 *
 * Created on May 7, 2012, 6:32 PM
 */

#ifndef VIRUS_H
#define	VIRUS_H

#include "PropertyMacro.h"
#include "ObjectPool.h"
#include "Type.h"

class Virus {
    OBJECTPOOL(Virus);
    PROPERTY(VirusStrain, strain);

public:
    Virus(VirusStrain strain = VirusStrain(-1, -1));
    Virus(const Virus& orig);
    virtual ~Virus();
private:

};

#endif	/* VIRUS_H */

