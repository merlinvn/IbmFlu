/* 
 * File:   StateTransitionQ.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 10:42 AM
 */
#include <math.h>

#include "StateTransitionQ.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"


StateTransitionQ::StateTransitionQ(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::QUARANTINED, random, state_transition_list, config) {
}

StateTransitionQ::~StateTransitionQ() {
}

NextState StateTransitionQ::GetNextState(Person* person) const {
    
    VirusStrain virus_strain = person->current_virus_strain();
    int time_to_progress_to_severity_or_recover = round(random()->RandomGamma(config()->gamma_coeff_time_to_progression_to_severity()[virus_strain.first][virus_strain.second], config()->coeff_others()));

    double r = random()->RandomUniform();

    if (r < (1 - config()->w()[virus_strain.first][virus_strain.second])) {
        //recover
        return NextState(time_to_progress_to_severity_or_recover, HostState::RECOVERED);
    }

    // if not recover then hospitalize
     return NextState(time_to_progress_to_severity_or_recover, HostState::HOSPITALIZED);

}