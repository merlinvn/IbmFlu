/* 
 * File:   StateTransitionH.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 10:55 AM
 */

#include <math.h>

#include "StateTransitionH.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"


StateTransitionH::StateTransitionH(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::HOSPITALIZED, random, state_transition_list, config) {
}

StateTransitionH::StateTransitionH(const StateTransitionH& orig) {
}

StateTransitionH::~StateTransitionH() {
}

NextState StateTransitionH::GetNextState(Person* person) const {
    VirusStrain virus_strain = person->current_virus_strain();    
    int time_to_progress_to_death_or_recover = round(random()->RandomGamma(config()->gamma_coeff_time_to_progression_to_death()[virus_strain.first][virus_strain.second],config()->coeff_others()));

    double r = random()->RandomUniform();

    if (r < (1 - config()->w_eta()[virus_strain.first][virus_strain.second])) {
        //recover
        return NextState(time_to_progress_to_death_or_recover, HostState::RECOVERED);
    }

    // if not recover then death
    return NextState(time_to_progress_to_death_or_recover, HostState::DEATH);
}