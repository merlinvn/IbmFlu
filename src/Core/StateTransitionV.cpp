/* 
 * File:   StateTransitionV.cpp
 * Author: merlin
 * 
 * Created on May 16, 2012, 10:51 AM
 */

#include <math.h>

#include "StateTransitionV.h"
#include "Person.h"
#include "Random.h"
#include "Config.h"

StateTransitionV::StateTransitionV(Random* random, StateTransitionPointerVector* state_transition_list, Config* config) : StateTransition(HostState::SEVERE, random, state_transition_list, config) {
}

StateTransitionV::StateTransitionV(const StateTransitionV& orig) {
}

StateTransitionV::~StateTransitionV() {
}

NextState StateTransitionV::GetNextState(Person* person) const {

    VirusStrain virus_strain = person->current_virus_strain();
    int time_to_progress_to_death_or_recover = round(random()->RandomGamma(config()->gamma_coeff_time_to_progression_to_death()[virus_strain.first][virus_strain.second],config()->coeff_others()));

    double r = random()->RandomUniform();

    if (r < (1 - config()->w()[virus_strain.first][virus_strain.second])) {
        //recover
        return NextState(time_to_progress_to_death_or_recover, HostState::RECOVERED);
    }

    // if not recover then death
    return NextState(time_to_progress_to_death_or_recover, HostState::DEATH);
}