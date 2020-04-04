/* 
 * File:   FarmReporter.cpp
 * Author: merlin
 * 
 * Created on May 21, 2012, 11:22 AM
 */

#include "FarmReporter.h"
#include "Model.h"
#include "Random.h"
#include "Scheduler.h"
#include "Population.h"
#include "Config.h"

FarmReporter::FarmReporter() {
}

FarmReporter::FarmReporter(const FarmReporter& orig) {
}

FarmReporter::~FarmReporter() {
}

void FarmReporter::DailyReport(Model* model) {
    if (model->CalculateAverageCaseFatality() != 0) {
        //omit the last one equal 0
        daily_case_fataolity_.push_back(model->CalculateAverageCaseFatality());
    }
}

void FarmReporter::BeforeRunReport(Model* model) {
    //farm report
    //    std::cout << "This is farm" << std::endl;
}

void FarmReporter::AfterRunReport(Model* model) {
    std::cout << model->random()->seed() << "\t"
            << model->scheduler()->current_time() << "\t"
            << model->config()->population_size()[0] << "\t"
            << model->config()->initial_strain().first << "\t"
            << model->config()->initial_strain().second << "\t"
            << model->CalulateR0() << "\t"
            << model->TotalNumberOfCases() << "\t"
            << model->population()->size(0, HostState::DEATH) << "\t"
            << model->CumulativeNumberOfMutations() << "\t"
            //            << model->IsInvasionOccured() << "\t"
            << model->CaseFatalityAt1000Cases() << "\t"
            //            << model->IsInvasionOccured() << "\t"
            << daily_case_fataolity_[daily_case_fataolity_.size() - 1] / daily_case_fataolity_[0] << "\t"
            << model->config()->q() << "\t"
            << model->config()->sd_reducing_by() << "\t"
            << std::endl;
}