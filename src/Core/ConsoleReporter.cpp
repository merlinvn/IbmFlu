/* 
 * File:   ConsoleDailyReporter.cpp
 * Author: merlin
 * 
 * Created on May 20, 2012, 1:56 PM
 */

#include "ConsoleReporter.h"
#include "HostState.h"
#include "Model.h"
#include "Config.h"
#include "Population.h"
#include "Scheduler.h"
#include "Random.h"

ConsoleReporter::ConsoleReporter() {
}

ConsoleReporter::~ConsoleReporter() {
}

void ConsoleReporter::DailyReport(Model* model) {
    if (model == NULL) return;
    //print total number of S-E-I-Q-S-H-R
    for (int loc = 0; loc < model->config()->number_of_locations(); loc++) {
        std::cout << model->scheduler()->current_time() << "\t";

        for (int hs = 0; hs < HostState::NUMBER; hs++) {
            std::cout << model->population()->size(0, (HostState::HostStates)hs) << "\t";
        }

        //output average case fatality

        std::cout << model->CalculateAverageCaseFatality() << "\t";
        std::cout << model->CumulativeNumberOfMutations() << "\t";

        std::cout << std::endl;
    }
}

void ConsoleReporter::AfterRunReport(Model* model) {
    std::cout << "==============================" << std::endl;

    //Calculate and report R0    
    std::cout << "R0 = " << model->CalulateR0() << std::endl;
//    std::cout << "Number of cases= " << model->TotalNumberOfCases() << std::endl;

}

void ConsoleReporter::BeforeRunReport(Model* model) {
    std::cout << "Seed = " << model->random()->seed() << std::endl;
}