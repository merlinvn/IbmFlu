/* 
 * File:   StateTransitionFromI.cpp
 * Author: merlin
 * 
 * Created on May 15, 2012, 3:24 PM
 */

#include <math.h>

#include "StateTransitionI.h"
#include "Config.h"
#include "Random.h"
#include "Person.h"
#include "Virus.h"

StateTransitionI::StateTransitionI(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::INFECTIOUS, random, state_transition_list, config) {

}

StateTransitionI::~StateTransitionI() {
}

NextState StateTransitionI::GetNextState(Person* person) const {

    // check whether this person will be quarantined
    double q = random()->RandomUniform();
    if (q < config()->q()) {
//        std::cout << q << std::endl;
        //quanrantined this person after next tau days
        int time_to_q = round(random()->RandomGamma(config()->gamma_coeff_tau_1(), config()->coeff_ItoQ()));          
        return NextState(time_to_q, HostState::QUARANTINED);

    }

    //not being quarantined
    VirusStrain virus_strain = person->current_virus_strain();
    int time_to_progress_to_severity_or_recover = round(random()->RandomGamma(config()->gamma_coeff_time_to_progression_to_severity()[virus_strain.first][virus_strain.second], config()->coeff_others()));    
    double r = random()->RandomUniform();
    if (r < (1 - config()->w()[virus_strain.first][virus_strain.second])) {
        //recover        
        return NextState(time_to_progress_to_severity_or_recover, HostState::RECOVERED);
    }

    // if not recover
    double h = random()->RandomUniform();
    if (h < config()->h()) {
        //hospitalized        
        return NextState(time_to_progress_to_severity_or_recover, HostState::HOSPITALIZED);
    }

    //otherwise move to Severe    
    return NextState(time_to_progress_to_severity_or_recover, HostState::SEVERE);

}