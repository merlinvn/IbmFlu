/* 
 * File:   FarmReporter2.cpp
 * Author: merlin
 * 
 * Created on June 25, 2012, 1:23 PM
 */

#include "FarmReporter2.h"
#include "Model.h"
#include "Random.h"
#include "Scheduler.h"
#include "Population.h"
#include "Config.h"
#include "Person.h"
#include <map>

FarmReporter2::FarmReporter2() {
}

FarmReporter2::FarmReporter2(const FarmReporter2& orig) {
}

FarmReporter2::~FarmReporter2() {
}

void FarmReporter2::DailyReport(Model* model) {
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
        //        if (!viralDistribution.empty()) {
        //            PairIntIntMapIterator itMax;
        //            int max = 0;
        //            for (PairIntIntMapIterator it = viralDistribution.begin(); it != viralDistribution.end(); it++) {
        //                if (max < (*it).second) {
        //                    max = (*it).second;
        //                    itMax = it;
        //                }
        //            }
        //            std::cout << (*itMax).first.first << "-" << (*itMax).first.second << ":" << (*itMax).second;
        //        }
        for (PairIntIntMapIterator it = viralDistribution.begin(); it != viralDistribution.end(); it++) {
            std::cout << (*it).first.first << "\t" << (*it).first.second << "\t" << (*it).second << "\t";
        }
        std::cout << std::endl;
    }


}

void FarmReporter2::BeforeRunReport(Model* model) {
    std::cout << model->random()->seed() << std::endl;
}

void FarmReporter2::AfterRunReport(Model* model) {
    std::cout << model->random()->seed() << "\t"
            << model->scheduler()->current_time() << "\t"
            << model->config()->population_size()[0] << "\t"
            << model->config()->initial_strain().first << "\t"
            << model->config()->initial_strain().second << "\t"
            << model->CalulateR0() << "\t"
            << model->TotalNumberOfCases() << "\t"
            << model->population()->size(0, HostState::DEATH) << "\t"
            << model->CumulativeNumberOfMutations() << "\t"
            << model->CaseFatalityAt1000Cases() << "\t"
//            << model->IsInvasionOccured() << "\t"
            << daily_case_fataolity_[daily_case_fataolity_.size() - 1] / daily_case_fataolity_[0] << "\t"
            << model->config()->q() << "\t"
            << model->config()->sd_reducing_by() << "\t";

    int step = (daily_case_fataolity_.size() / 5);
    step = (step < 1) ? 1 : step;

    int count = 0;
    for (int i = 0; i < daily_case_fataolity_.size() && (count <= 6); i += step) {
        std::cout << i << "\t" << daily_case_fataolity_[i] << "\t";
        count++;
    }

    if (count < 6) {
        std::cout << daily_case_fataolity_.size() - 1 << "\t" << daily_case_fataolity_[daily_case_fataolity_.size() - 1] << "\t";
    }

    PairIntIntMap viralDistribution = model->getViralDistribution();

    for (PairIntIntMapIterator it = viralDistribution.begin(); it != viralDistribution.end(); it++) {
        std::cout << (*it).first.first << "\t" << (*it).first.second << "\t" << (*it).second << "\t";
    }

    std::cout << std::endl;
}
