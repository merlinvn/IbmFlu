/* 
 * File:   HostState.h
 * Author: merlin
 *
 * Created on May 9, 2012, 10:12 AM
 */

#ifndef HOSTSTATE_H
#define	HOSTSTATE_H

namespace HostState {

    enum HostStates {
        SUSCEPTIBLE = 0,
        EXPOSED = 1,
        INFECTIOUS = 2,
        QUARANTINED = 3,
        SEVERE = 4,
        HOSPITALIZED = 5,
        RECOVERED = 6,
        DEATH = 7,
        NUMBER = 8
    };
}



#endif	/* HOSTSTATE_H */

