/* 
 * File:   Model.h
 * Author: merlin
 *
 * Created on May 11, 2012, 1:00 PM
 */

#ifndef MODEL_H
#define	MODEL_H

#include <iostream>
#include <list>
#include "PropertyMacro.h"
#include "StateTransition.h"
#include "Type.h"

class Config;
class Scheduler;
class Population;
class Random;
class Reporter;

class Model {
    POINTER_PROPERTY(Config, config);

    POINTER_PROPERTY(StateTransition::StateTransitionPointerVector, state_transition_list);

    POINTER_PROPERTY(Scheduler, scheduler);

    POINTER_PROPERTY(Population, population);

    POINTER_PROPERTY(Random, random);

    PROPERTY(ReporterList, afer_run_reporters);

    PROPERTY(PersonVector, initial_cases);
    
    PROPERTY(int, CumulativeNumberOfMutations);
    PROPERTY(double, CaseFatalityAt1000Cases);
    
    PROPERTY(int, social_distance_start_at);
    PROPERTY(double, reducing_factor);

public:
    Model();
    Model(const Model& orig);
    virtual ~Model();

    void Initialize(const unsigned int& seed = -1, const std::string& input_file = "config.yml", const std::string& override_file = "", const int& override_pos = 1);

    void InitiallizeFirstCase();

    void Run();
    
    void BeforeRun();

    void AfterRun();

    void Release();

    void CreateTransitionList();

    void PerformInfectionEvents();
    void PerformMutationEvents();
    void CleanUpIndividualsWithDeathState();

    void RegisterReporter(Reporter* reporter);


    double CalulateR0();

    double CalculateAverageCaseFatality();
    
    int TotalNumberOfCases();
    
    PairIntIntMap getViralDistribution();
    PairIntIntMap getCurrentViralDistribution();
    
    bool IsInvasionOccured();
    
private:

    void InitializeObjectPool();
    void ReleaseObjectPool();



};

#endif	/* MODEL_H */

