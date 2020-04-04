/* 
 * File:   FarmReporter4.cpp
 * Author: merlin
 * 
 * Created on August 17, 2012, 10:31 AM
 */

#include "FarmReporter4.h"
#include "Model.h"
#include "Config.h"
#include "Random.h"
#include "Scheduler.h"
#include "Population.h"

FarmReporter4::FarmReporter4() {
}

FarmReporter4::FarmReporter4(const FarmReporter4& orig) {
}

FarmReporter4::~FarmReporter4() {
}

void FarmReporter4::DailyReport(Model* model) {
    if (model->CalculateAverageCaseFatality() != 0) {
        //omit the last one equal 0
        daily_case_fataolity_.push_back(model->CalculateAverageCaseFatality());
    }

}

void FarmReporter4::BeforeRunReport(Model* model) {

}

void FarmReporter4::AfterRunReport(Model* model) {
    std::cout << model->random()->seed() << "\t"
            << model->scheduler()->current_time() << "\t"
            << model->config()->population_size()[0] << "\t"
            << model->config()->initial_strain().first << "\t"
            << model->config()->initial_strain().second << "\t"
            << model->config()->R0max() << "\t"
            << model->config()->mutation_rate() << "\t"
            << model->config()->sigmaI() << "\t"
            << model->config()->sigmaV() << "\t"
            << model->config()->B_a2() << "\t"
            << model->config()->B_c() << "\t"
            << model->config()->q() << "\t"
            << model->config()->h() << "\t"
            << model->config()->zQ() << "\t"
            << model->config()->zV() << "\t"
            << model->config()->tau_1()<< "\t"
            //======== output ////////
            << model->CalulateR0() << "\t"
            << model->TotalNumberOfCases() << "\t"
            << model->population()->size(0, HostState::DEATH) << "\t"
            << model->CumulativeNumberOfMutations() << "\t"
            << model->CaseFatalityAt1000Cases() << "\t"
            << daily_case_fataolity_[daily_case_fataolity_.size() - 1] / daily_case_fataolity_[0] << "\t"
            << std::endl;
}