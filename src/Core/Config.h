/* 
 * File:   Config.h
 * Author: merlin
 *
 * Created on May 11, 2012, 1:00 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include "PropertyMacro.h"
#include "Person.h"
#include <vector>
#include "Type.h"


/*
 * Config class will contain all parameter read from the input file or command line
 */
class Config {
    DISALLOW_COPY_AND_ASSIGN_(Config);

    //M and N will be read from input file
    //total number of degree of affinity (j = 1..M)
    VIRTUAL_PROPERTY(int, M);

    //total number of virus replicative ability (k = 1..N)
    VIRTUAL_PROPERTY(int, N);
    
    //total of number of days in the simulation
    VIRTUAL_PROPERTY(int, total_time);
    
    //total of number of locations in the simulation
    VIRTUAL_PROPERTY(int, number_of_locations);
    
    VIRTUAL_PROPERTY(IntVector, population_size);
    
    //total of number of age class in the simulation
    VIRTUAL_PROPERTY(int, number_of_age_classes);
    VIRTUAL_PROPERTY(DoubleVector, age_distribution);
    
    //fraction of I-individuals will be quarantined
    VIRTUAL_PROPERTY(double, q);
    
    //fraction of individual in I and Q can progress to severe disease (strain-specific)
    //this also the fraction of severely infected individuals will die (strain-specific)
    // this w will be calculated from B and CFmax (read from input file)
    VIRTUAL_PROPERTY(DoubleMatrix, w);
    //mortality rate for H-Individuals
    VIRTUAL_PROPERTY(DoubleMatrix, w_eta);           
    
    //fraction of I individuals progressing to severe disease are hospitalized
    VIRTUAL_PROPERTY(double, h);
    
    //eta: reduced factor of mortality for H-Individuals
    VIRTUAL_PROPERTY(double, eta);           
    

    //alpha will be read directly from input file
    VIRTUAL_PROPERTY(DoubleVector, alpha);

    //beta will be calculated from a0, a1 read from input file
    VIRTUAL_PROPERTY(DoubleVector, beta);
   
    //recovery rate v: minimum recovery rates for infected individuals (input file)
    VIRTUAL_PROPERTY(double, v);
    //recovery rate vv: minimum recovery rates for severely infected individuals (input file) 
    VIRTUAL_PROPERTY(double, vv);    
            
    //virual burden B will be calculated based on alpha, N (population size), c,and a2 read from input file
    VIRTUAL_PROPERTY(DoubleMatrix, B);

    
    //host in I and Q classes progress to severity at rate v + pi[j,k] = v(1+ sigmaI*B[j,k])
    VIRTUAL_PROPERTY(DoubleMatrix, time_to_progression_to_severity);
    VIRTUAL_PROPERTY(DoubleMatrix, gamma_coeff_time_to_progression_to_severity);
    
    //host in V and H classes progress to severity at rate vv + phi[j,k]
    // phi[j,k] will be calculated based on vv, B, sigmaV (read from input)
    VIRTUAL_PROPERTY(DoubleMatrix, time_to_progression_to_death);
    VIRTUAL_PROPERTY(DoubleMatrix, gamma_coeff_time_to_progression_to_death);
    
    //mutation rate read from input file
    VIRTUAL_PROPERTY(double, mutation_rate);
    
    //tau^-1: time form symptoms to quarantine, read from input file
    VIRTUAL_PROPERTY(double, tau_1);
    VIRTUAL_PROPERTY(double, gamma_coeff_tau_1);
    
    VIRTUAL_PROPERTY(double, time_E_to_I);    
    VIRTUAL_PROPERTY(double, gamma_coeff_time_E_to_I);    
    
    //level of mixing
    VIRTUAL_PROPERTY(double, zI);
    VIRTUAL_PROPERTY(double, zQ);
    VIRTUAL_PROPERTY(double, zV);
    VIRTUAL_PROPERTY(double, zH);
    
    VIRTUAL_PROPERTY(DoubleVector, z);
    
    //initial cases
    VIRTUAL_PROPERTY(int, number_of_initial_cases);
    VIRTUAL_PROPERTY(VirusStrain, initial_strain);
    
    VIRTUAL_PROPERTY(int, number_of_generations_for_R0);   
    
    VIRTUAL_PROPERTY(double, coeff_EtoI);
    VIRTUAL_PROPERTY(double, coeff_ItoQ);
    VIRTUAL_PROPERTY(double, coeff_others);
    
    VIRTUAL_PROPERTY(int, report_period);
    
    VIRTUAL_PROPERTY(int, sd_trigger_at);
    VIRTUAL_PROPERTY(double, sd_reducing_by);
    VIRTUAL_PROPERTY(int, sd_relaxing_in);

    VIRTUAL_PROPERTY(double, R0max);
    VIRTUAL_PROPERTY(double, sigmaI);
    VIRTUAL_PROPERTY(double, sigmaV);
    
    VIRTUAL_PROPERTY(double, B_c);
    VIRTUAL_PROPERTY(double, B_a2);
public:
    Config();
    virtual ~Config();
    
    void ReadFromFile(const std::string& fileName);
    
    void OverrideParameters(const std::string& override_file, const int& pos);
    void OverrideParameter(const std::string& paramenter_name, const std::string& parameter_value);
    
    void CalculateDependentVariables();
    
    void CalculateAlpha();
    void CalculateBeta();
    void CalculateViralBurden();
    
    void CalculateRateOfProgressionToSeverity();
    void CalculateRateOfProgressionToDeath();
    
    void CalculateWParameter();
    void ReCalculateBeta_a0();
    
    
private:    
    
    double CFMax_;
    
    double alpha_min_;
    double alpha_max_;
    
    double beta_a0_;
    double beta_a1_;
//    
//    double B_c_;
//    double B_a2_;
    
    
    
    double G_MAX_R0_;
    
};

#endif	/* CONFIG_H */

