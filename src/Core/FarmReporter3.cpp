/* 
 * File:   FarmReporter3.cpp
 * Author: merlin
 * 
 * Created on July 1, 2012, 10:01 AM
 */

#include "FarmReporter3.h"
#include "Model.h"
#include "Random.h"
#include "Scheduler.h"
#include "Population.h"
#include "Config.h"
#include "Person.h"
#include <map>

FarmReporter3::FarmReporter3() {
}

FarmReporter3::FarmReporter3(const FarmReporter3& orig) {
}

FarmReporter3::~FarmReporter3() {
}

void FarmReporter3::DailyReport(Model* model) {
    if (model->CalculateAverageCaseFatality() != 0) {
        //omit the last one equal 0
        daily_case_fataolity_.push_back(model->CalculateAverageCaseFatality());
    }


    if (model->scheduler()->current_time() % model->config()->report_period() == 0) {
        std::cout << model->scheduler()->current_time() << "\t";

        for (int hs = 0; hs < HostState::NUMBER; hs++) {
            std::cout << model->population()->size(0, (HostState::HostStates)hs) << "\t";
        }
        std::cout << model->CalculateAverageCaseFatality() << "\t";

        PairIntIntMap viralDistribution = model->getCurrentViralDistribution();
        for (PairIntIntMapIterator it = viralDistribution.begin(); it != viralDistribution.end(); it++) {
            std::cout << (*it).first.first << "\t" << (*it).first.second << "\t" << (*it).second << "\t";
        }
        std::cout << std::endl;
    }


}

void FarmReporter3::BeforeRunReport(Model* model) {

}

void PrintTransmissionGraph(Person* person, const int& maxGen, const int& parentGeneration) {
    int currentGeneration = parentGeneration + 1;
    if (currentGeneration == maxGen) {
        return;
    }

    for (PersonVectorIterator it = person->infected_individuals()->begin(); it != person->infected_individuals()->end(); it++) {
        std::cout << "\"" << person << "\"" << "->" << "\"" << (*it) << "\"" << ";" << std::endl;

        PrintTransmissionGraph(*it, maxGen, currentGeneration);
    }
}

void FarmReporter3::AfterRunReport(Model* model) {
    // print transmission graph up to n generation
    std::cout << "digraph G {" << std::endl;

    for (PersonVectorIterator it = model->initial_cases().begin(); it != model->initial_cases().end(); it++) {
        int currentGeneration = 0;
        //traverse the tree until reach number of generation in config
        PrintTransmissionGraph((*it), 7, currentGeneration);
    }
    std::cout << "}" << std::endl;
}
