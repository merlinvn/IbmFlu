/* 
 * File:   Model.cpp
 * Author: merlin
 * 
 * Created on May 11, 2012, 1:00 PM
 */
#include <assert.h>

#include "Model.h"
#include "Config.h"
#include "ChangeStateEvent.h"
#include "Scheduler.h"
#include "Population.h"
#include "Random.h"
#include "StateTransitionE.h"
#include "StateTransitionQ.h"
#include "StateTransitionV.h"
#include "StateTransitionH.h"
#include "StateTransitionI.h"
#include "StateTransitionS.h"
#include "StateTransitionD.h"
#include "Virus.h"
#include "Reporter.h"
#include "StateTransitionR.h"

Model::Model() : config_(NULL), population_(NULL), state_transition_list_(NULL), scheduler_(NULL), CumulativeNumberOfMutations_(0) {
}

Model::Model(const Model& orig) {
}

Model::~Model() {

}

void Model::Initialize(const unsigned int& seed, const std::string& input_file, const std::string& override_file, const int& override_pos) {

    //Initialize ObjectPool
    InitializeObjectPool();

    //Initialize Random Generator
    random_ = new Random();
    random_->Initialize(seed);
    //read input file
    config_ = new Config();
    config_->ReadFromFile(input_file);

    //override config parameter if needed
    config_->OverrideParameters(override_file, override_pos);
    //create transition list
    CreateTransitionList();


    //create scheduler
    scheduler_ = new Scheduler(this, config_->total_time() + 1000, 0);

    //create empty population
    population_ = new Population(this, config_->number_of_locations(), config_->number_of_age_classes(), config_->M(), config_->N());
    //...

    //create individuals in population
    population_->Initialize(config_);    
    
    CaseFatalityAt1000Cases_ = 0;
    
    social_distance_start_at_ = -1;
    reducing_factor_ = 1;
}

void Model::Run() {
    //TODO:: beforRun

    BeforeRun();

    scheduler_->Run();

    AfterRun();
    //TODO:: afterRun
}

void Model::Release() {

    if (scheduler_ != NULL) delete scheduler_;


    if (population_ != NULL) delete population_;

    if (state_transition_list_ != NULL) {
        for (StateTransition::StateTransitionPointerVector::iterator it = state_transition_list_->begin(); it != state_transition_list_->end(); it++) {
            delete (*it);
        }
        delete state_transition_list_;
    }

    if (config_ != NULL) delete config_;

    if (random_ != NULL) delete random_;

    //release Reporter
    for (ReporterList::iterator it = afer_run_reporters_.begin(); it != afer_run_reporters_.end(); it++) {
        delete (*it);
    }

    //release ObjectPool
    ReleaseObjectPool();

}

void Model::InitializeObjectPool() {
    Virus::InitializeObjectPool();
    ChangeStateEvent::InitializeObjectPool();
    Person::InitializeObjectPool();

}

void Model::ReleaseObjectPool() {

    Person::ReleaseObjectPool();
    ChangeStateEvent::ReleaseObjectPool();
    Virus::ReleaseObjectPool();
}

void Model::CreateTransitionList() {
    state_transition_list_ = new StateTransition::StateTransitionPointerVector(HostState::NUMBER, NULL);

    (*state_transition_list_)[HostState::SUSCEPTIBLE] = new StateTransitionS(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::EXPOSED] = new StateTransitionE(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::INFECTIOUS] = new StateTransitionI(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::QUARANTINED] = new StateTransitionQ(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::SEVERE] = new StateTransitionV(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::HOSPITALIZED] = new StateTransitionH(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::RECOVERED] = new StateTransitionR(random_, state_transition_list_, config_);
    (*state_transition_list_)[HostState::DEATH] = new StateTransitionD(random_, state_transition_list_, config_);
}

void Model::InitiallizeFirstCase() {

    int number_of_cases = config()->number_of_initial_cases();
    //    std::cout << config_->initial_strain().first << "-" <<config_->initial_strain().second << std::endl;
    //    std::cout << config_->beta()[100]<< std::endl;
    for (int i = 0; i < number_of_cases; i++) {
        VirusStrain vr = config_->initial_strain();
        //select random a person then infect him with a particular Virus Strain
        int index = random_->RandomUniform(population_->size(0));
        Person* p = population_->personIndexAll->vPerson[index];

        p->Infect(vr);
        p->set_state(HostState::EXPOSED);

        initial_cases_.push_back(p);

        StateTransition* stateTransition = (*state_transition_list_)[HostState::EXPOSED];
        NextState nextState = stateTransition->GetNextState(p);

        if (nextState.second < HostState::NUMBER) {
            StateTransition* nextStateTransition = (*state_transition_list_)[nextState.second];
            ChangeStateEvent* event = new ChangeStateEvent(nextState.first, p, true, scheduler(), nextStateTransition);
            scheduler()->Schedule(event);
        }
    }
}

/*TODO:: unit test for this function
 */

void Model::PerformInfectionEvents() {
    for (int location = 0; location < config_->number_of_locations(); location++) {
        int population_size_by_location = population_->size(location);
        std::vector<Person*> infectionList;
        //for each strain
        for (int j = 0; j < config_->M(); j++) {
            for (int k = 0; k < config_->N(); k++) {
                //calculate force of infection for each jk                                     

                for (int state = HostState::INFECTIOUS; state <= HostState::HOSPITALIZED; state++) {
                    int popSizeByState = population_->size(location, (HostState::HostStates)state, j, k);
                    double force_infection_jk = (config_->alpha()[j] * config_->beta()[k] / population_size_by_location)*
                            (config_->z()[state] * popSizeByState);
                    
//                    std::cout << config_->z()[state]<< std::endl;

                    for (int age_class = 0; age_class < config_->number_of_age_classes(); age_class++) {
                        int number_of_susceptible = population_->size(location, HostState::SUSCEPTIBLE, age_class);
                        double poison_mean = reducing_factor_* force_infection_jk * number_of_susceptible;
                        int number_of_new_infections = random_->RandomPoisson(poison_mean);

                        for (int i = 0; i < number_of_new_infections; i++) {
                            //select random S-individual in this age class
                            int infection_index = random_->RandomUniform(number_of_susceptible);

                            //infection source
                            int index = random_->RandomUniform(popSizeByState);

                            Person* infect_source = population_->at(location, (HostState::HostStates)state, j, k, index);
                            Person* p = population_->new_infect_individual(location, age_class, infection_index, VirusStrain(j, k), infect_source);
                            infectionList.push_back(p);
                        }

                    }
                }
            }
        }

        //resolve infection list
        for (std::vector<Person*>::iterator it = infectionList.begin(); it != infectionList.end(); it++) {
            Person* p = (*it);
            if (p->today_infection_list()->size() != 0) {
                p->resolve_infection_list(this);

                //change state to expose today
                ChangeStateEvent* event = new ChangeStateEvent(scheduler_->current_time(), p, true, scheduler(), (*state_transition_list_)[HostState::EXPOSED]);
                scheduler()->Schedule(event);
            }
        }

    }
}

void Model::PerformMutationEvents() {
    std::vector<Person*> mutationList;
    for (int location = 0; location < config_->number_of_locations(); location++) {
        for (int state = HostState::EXPOSED; state <= HostState::HOSPITALIZED; state++) {
            for (int age_class = 0; age_class < config_->number_of_age_classes(); age_class++) {
                int pop_size_by_state = population_->size(location, (HostState::HostStates)state, age_class);
                if (pop_size_by_state == 0) continue;
                //                std::cout << state << "-" << age_class << "-" << pop_size_by_state<< std::endl;
                double poison_mean = pop_size_by_state * config_->mutation_rate();
                int number_of_mutations = random_->RandomPoisson(poison_mean);

                for (int i = 0; i < number_of_mutations; i++) {
                    int mutation_index = random_->RandomUniform(pop_size_by_state);
                    Person* p = population_->at(location, (HostState::HostStates)state, age_class, mutation_index);

                    mutationList.push_back(p);
                }
            }
        }
    }

    //resolve mutation list    
    for (std::vector<Person*>::iterator it = mutationList.begin(); it != mutationList.end(); it++) {
        Person* p = (*it);
        p->mutate_virus(random_, config_->M() - 1, config_->N() - 1);
        CumulativeNumberOfMutations_++;
    }
}

void Model::CleanUpIndividualsWithDeathState() {
    //    population_->CleanUpIndividualsWithDeathState();
}

void Model::RegisterReporter(Reporter* reporter) {
    scheduler_->RegisterDailyReporter(reporter);
    afer_run_reporters_.push_back(reporter);

}

void Model::BeforeRun() {
    for (ReporterList::iterator it = afer_run_reporters_.begin(); it != afer_run_reporters_.end(); it++) {
        (*it)->BeforeRunReport(this);
    }
}

void Model::AfterRun() {
    for (ReporterList::iterator it = afer_run_reporters_.begin(); it != afer_run_reporters_.end(); it++) {
        (*it)->AfterRunReport(this);
    }
}

void TrackInfectedPerson(Person* person, const int& maxGen, const int& parentGeneration, int& numberOfInfectors, int& numberOfSecondaryCases) {
    int currentGeneration = parentGeneration + 1;
    numberOfInfectors += 1;
    numberOfSecondaryCases += person->infected_individuals()->size();
    //    std::cout << currentGeneration << "-" << person->infected_individuals()->size() << "-" << numberOfInfectors << "-" << numberOfSecondaryCases << std::endl;
    if (currentGeneration == maxGen) {
        return;
    }

    for (PersonVectorIterator it = person->infected_individuals()->begin(); it != person->infected_individuals()->end(); it++) {
        TrackInfectedPerson(*it, maxGen, currentGeneration, numberOfInfectors, numberOfSecondaryCases);
    }
}

double Model::CalulateR0() {
    //    std::cout << "Infection tree:" << std::endl;
    //    std::cout << "Generation" << " - " << "Number of infections in current node" << " - " << "Number of infectors" << " - " << "Number of infections" << std::endl;
    double results = 0;

    int numberOfSecondaryCases = 0;
    int numberOfInfectors = 0;

    for (PersonVectorIterator it = initial_cases_.begin(); it != initial_cases_.end(); it++) {
        int currentGeneration = 0;
        //traverse the tree until reach number of generation in config
        TrackInfectedPerson((*it), config_->number_of_generations_for_R0(), currentGeneration, numberOfInfectors, numberOfSecondaryCases);
    }
    //    std::cout << numberOfSecondaryCases << "-" << numberOfInfectors << std::endl;
    return (numberOfInfectors == 0) ? 0 : numberOfSecondaryCases / (double) numberOfInfectors;
}

double Model::CalculateAverageCaseFatality() {

    int totalNumberOfCases = 0;
    double totalCaseFatality = 0;

    //for each location
    for (int loc = 0; loc < config_->number_of_locations(); loc++) {
        //for each state
        for (int state = HostState::EXPOSED; state <= HostState::HOSPITALIZED; state++) {
            // for each strains
            for (int j = 0; j < config_->M(); j++) {
                for (int k = 0; k < config_->N(); k++) {
                    // sum the number of cases 
                    // sum up total case fatality
                    int numberOfCases = population_->size(loc, (HostState::HostStates)state, j, k);
                    totalNumberOfCases += numberOfCases;
                    totalCaseFatality += numberOfCases * config_->w()[j][k] * config_->w()[j][k];
                }
            }
        }
    }
    return (totalNumberOfCases == 0) ? 0 : totalCaseFatality / totalNumberOfCases;
}

int Model::TotalNumberOfCases() {
    int results = 0;
    for (int loc = 0; loc < config_->number_of_locations(); loc++) {
        for (int state = HostState::EXPOSED; state <= HostState::DEATH; state++) {
            results += population_->size(loc, (HostState::HostStates)state);
        }
    }
    return results;

}

PairIntIntMap Model::getViralDistribution() {
    PairIntIntMap viralDistribution;

    for (int loc = 0; loc < config()->number_of_locations(); loc++) {
        for (int hs = HostState::EXPOSED; hs <= HostState::DEATH; hs++) {
            for (int ac = 0; ac < config()->number_of_age_classes(); ac++) {
                for (int i = 0; i < population()->personIndexByLocationStateAgeClass->vPerson[loc][hs][ac].size(); i++) {
                    Person* p = population()->personIndexByLocationStateAgeClass->vPerson[loc][hs][ac][i];
                    VirusStrain index;
                    if (p->current_virus() == NULL) {
                        index = p->last_infected_strain();
                    } else {
                        index = p->current_virus_strain();
                    }

                    if (viralDistribution.find(index) == viralDistribution.end()) {
                        viralDistribution[index] = 1;
                    } else {
                        viralDistribution[index] += 1;
                    }
                }
            }
        }
    }
    return viralDistribution;
}

PairIntIntMap Model::getCurrentViralDistribution() {
    PairIntIntMap viralDistribution;
    for (int loc = 0; loc < config()->number_of_locations(); loc++) {
        for (int hs = HostState::EXPOSED; hs <= HostState::HOSPITALIZED; hs++) {
            for (int ac = 0; ac < config()->number_of_age_classes(); ac++) {
                for (int i = 0; i < population()->personIndexByLocationStateAgeClass->vPerson[loc][hs][ac].size(); i++) {
                    Person* p = population()->personIndexByLocationStateAgeClass->vPerson[loc][hs][ac][i];
                    VirusStrain index;
                    if (p->current_virus() == NULL) {
                        index = p->last_infected_strain();
                    } else {
                        index = p->current_virus_strain();
                    }

                    if (viralDistribution.find(index) == viralDistribution.end()) {
                        viralDistribution[index] = 1;
                    } else {
                        viralDistribution[index] += 1;
                    }
                }
            }
        }
    }
    return viralDistribution;
}

bool Model::IsInvasionOccured() {
    int numberOfCases = 0;

    for (int loc = 0; loc < config()->number_of_locations(); loc++) {
        for (int hs = HostState::EXPOSED; hs <= HostState::DEATH; hs++) {
            for (int ac = 0; ac < config()->number_of_age_classes(); ac++) {
                numberOfCases += population_->size(loc, (HostState::HostStates)hs, ac);
            }
        }
    }
    return numberOfCases >= 1000;
}