/* 
 * File:   Config.cpp
 * Author: merlin
 * 
 * Created on May 11, 2012, 1:00 PM
 */

#include "Config.h"
#include "yaml-cpp/yaml.h"
#include <fstream>

Config::Config() {
}

Config::~Config() {
}

void Config::ReadFromFile(const std::string &fileName) {
  YAML::Node config = YAML::LoadFile(fileName);

  total_time_ = config["total_time"].as<int>();

  number_of_locations_ = config["number_of_locations"].as<int>();
  number_of_age_classes_ = config["number_of_age_classes"].as<int>();



  YAML::Node popNode = config["population_size"];
  for (std::size_t i = 0; i < number_of_locations_; i++) {
    population_size_.push_back(popNode[i].as<double>());
  }

  if (number_of_age_classes_ == 1) {
    age_distribution_.push_back(1);
  } else {
    //read age distribution
    YAML::Node ad = config["age_distribution"];
    for (std::size_t i = 0; i < ad.size(); i++) {
      age_distribution_.push_back(ad[i].as<double>());
    }
  }

  M_ = config["M"].as<int>();
  N_ = config["N"].as<int>();

  q_ = config["q"].as<double>();


  CFMax_ = config["CFmax"].as<double>();

  alpha_min_ = config["alpha"]["min"].as<double>();
  alpha_max_ = config["alpha"]["max"].as<double>();


  beta_a0_ = config["beta"]["a0"].as<double>();
  beta_a1_ = config["beta"]["a1"].as<double>();

  B_c_ = config["B"]["c"].as<double>();
  B_a2_ = config["B"]["a2"].as<double>();

  h_ = config["h"].as<double>();

  eta_ = config["eta"].as<double>();

  v_ = config["v"].as<double>();
  vv_ = config["vv"].as<double>();

  sigmaI_ = config["sigmaI"].as<double>();

  sigmaV_ = config["sigmaV"].as<double>();

  mutation_rate_ = config["mutation_rate"].as<double>();

  tau_1_ = config["tau_1"].as<double>();

  time_E_to_I_ = config["time_E_to_I"].as<double>();

  zI_ = config["level_of_mixing"]["zI"].as<double>();
  zQ_ = config["level_of_mixing"]["zQ"].as<double>();
  zV_ = config["level_of_mixing"]["zV"].as<double>();
  zH_ = config["level_of_mixing"]["zH"].as<double>();

  //read initial cases
  number_of_initial_cases_ = config["initial_cases"]["number"].as<int>();
  initial_strain_.first = config["initial_cases"]["strain"][0].as<int>();
  initial_strain_.second = config["initial_cases"]["strain"][1].as<int>();

  number_of_generations_for_R0_ = config["number_of_generations_for_R0"].as<int>();

  coeff_EtoI_ = config["coeff_EtoI"].as<double>();
  coeff_ItoQ_ = config["coeff_ItoQ"].as<double>();
  coeff_others_ = config["coeff_others"].as<double>();


  report_period_ = config["report_period"].as<int>();

  sd_trigger_at_ = config["social_distancing"]["trigger_at"].as<int>();
  sd_reducing_by_ = config["social_distancing"]["reducing_by"].as<double>();
  sd_relaxing_in_ = config["social_distancing"]["relaxing_in"].as<int>();

  R0max_ = config["R0max"].as<double>();
  //calculate dependent variables
  CalculateDependentVariables();
  //    ReCalculateBeta_a0();
  //    CalculateDependentVariables();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  return split(s, delim, elems);
}

void Config::OverrideParameters(const std::string &override_file, const int &pos) {

  //open file
  std::ifstream ifs(override_file.c_str());
  if (!ifs && override_file != "") {
    std::cout << "Error" << std::endl;
  }

  std::string buf;
  getline(ifs, buf);

  //header of file containt all overrides parameters name
  std::vector<std::string> override_header = split(buf, '\t');


  //goto the pos line in the file
  for (int i = 0; (i < pos) && getline(ifs, buf); i++) {
  }
  //buff contain the parameters
  std::vector<std::string> override_parameters = split(buf, '\t');

  //override parameter
  for (int i = 0; i < override_parameters.size(); i++) {
    if (override_parameters[i] != "nil") {
      OverrideParameter(override_header[i], override_parameters[i]);
    }
  }
  //re-calculate dependent variables
  CalculateDependentVariables();
}

void Config::OverrideParameter(const std::string &paramenter_name, const std::string &parameter_value) {
  //    population_size	M	N	initial_i	initial_j       sd_reducing_by
  if (paramenter_name == "population_size") {
    population_size_[0] = atoi(parameter_value.c_str());
  } else if (paramenter_name == "M") {
    M_ = atoi(parameter_value.c_str());
  } else if (paramenter_name == "N") {
    N_ = atoi(parameter_value.c_str());
  } else if (paramenter_name == "initial_j") {
    initial_strain_.first = atoi(parameter_value.c_str());
  } else if (paramenter_name == "initial_k") {
    initial_strain_.second = atoi(parameter_value.c_str());
  } else if (paramenter_name == "sd_reducing_by") {
    sd_reducing_by_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "R0max") {
    R0max_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "mu") {
    mutation_rate_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "sigmaI") {
    sigmaI_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "sigmaV") {
    sigmaV_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "a2") {
    B_a2_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "c") {
    B_c_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "tau_1") {
    tau_1_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "q") {
    q_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "h") {
    h_ = atof(parameter_value.c_str());
  } else if (paramenter_name == "zQzH") {
    zQ_ = atof(parameter_value.c_str());
    zH_ = zQ_;
  } else if (paramenter_name == "zV") {
    zV_ = atof(parameter_value.c_str());
  }


  //Put more parameters here
}

void Config::CalculateDependentVariables() {
  CalculateAlpha();
  CalculateBeta();

  CalculateViralBurden();

  CalculateRateOfProgressionToSeverity();
  CalculateRateOfProgressionToDeath();

  // w parameters
  CalculateWParameter();

  //calculate z parameters;
  z_.clear();
  z_.push_back(0.0);
  z_.push_back(0.0);
  z_.push_back(zI_);
  z_.push_back(zQ_);
  z_.push_back(zV_);
  z_.push_back(zH_);
  z_.push_back(0);
  z_.push_back(0);

  //calculate gamma coeff E to I
  gamma_coeff_time_E_to_I_ = time_E_to_I_ / coeff_EtoI_;

  //calculate Gamma Coeff for tau_1
  gamma_coeff_tau_1_ = tau_1_ / coeff_ItoQ_;

  ReCalculateBeta_a0();
  CalculateBeta();

}

void Config::CalculateAlpha() {
  alpha_ = DoubleVector(M_, 0);
  double step = (alpha_max_ - alpha_min_) / (M_ - 1);

  double value = alpha_min_;
  for (int j = 0; j < M_; j++) {
    alpha_[j] = value;
    value += step;
    //        std::cout << alpha_[j] << "\t";
  }
  //    std::cout << std::endl;
}

void Config::CalculateBeta() {
  beta_ = DoubleVector(N_, 0.0);
  double value = 0;

  for (int k = 0; k < N_; k++) {
    value = (beta_a0_ * (k + 1)) / (beta_a1_ + (k + 1));
    beta_[k] = value;
    //        std::cout << beta_[k] << " ";
  }
  //    std::cout << std::endl;
}

void Config::CalculateViralBurden() {
  //TODO: multiple location
  B_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));
  for (int j = 0; j < M_; j++) {
    for (int k = 0; k < N_; k++) {
      double v1 = (1 - alpha_[j]) * ((k + 1) / (double) N_);
      double v2 = B_a2_ * pow(((k + 1) / (double) N_), B_c_);
      B_[j][k] = (v1 + v2) / (1 + B_a2_);
      //            std::cout << B_[j][k] << "\t";
    }
    //        std::cout << std::endl;
  }
}

void Config::CalculateRateOfProgressionToSeverity() {
  time_to_progression_to_severity_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));
  gamma_coeff_time_to_progression_to_severity_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));

  for (int j = 0; j < M_; j++) {
    for (int k = 0; k < N_; k++) {
      time_to_progression_to_severity_[j][k] = 1 / (v_ * (1 + sigmaI_ * B_[j][k]));
      gamma_coeff_time_to_progression_to_severity_[j][k] = time_to_progression_to_severity_[j][k] / coeff_others_;
      //            std::cout << time_to_progression_to_severity_[j][k] << " ";
    }
    //        std::cout << std::endl;
  }
}

void Config::CalculateRateOfProgressionToDeath() {
  time_to_progression_to_death_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));
  gamma_coeff_time_to_progression_to_death_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));

  for (int j = 0; j < M_; j++) {
    for (int k = 0; k < N_; k++) {
      time_to_progression_to_death_[j][k] = 1 / (vv_ * (1 + sigmaV_ * B_[j][k]));
      gamma_coeff_time_to_progression_to_death_[j][k] = time_to_progression_to_death_[j][k] / coeff_others_;

//            std::cout << time_to_progression_to_death_[j][k] << " ";
    }
//        std::cout << std::endl;
  }
}

void Config::CalculateWParameter() {
  w_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));
  w_eta_ = DoubleMatrix(M_, DoubleVector(N_, 0.0));

  for (int j = 0; j < M_; j++) {
    for (int k = 0; k < N_; k++) {
      w_[j][k] = sqrt(B_[j][k] * CFMax_);
      w_eta_[j][k] = eta_ * w_[j][k];
      //            std::cout << w_[j][k]*w_[j][k] << "\t";
    }
    //        std::cout << std::endl;
  }
}

void Config::ReCalculateBeta_a0() {
  G_MAX_R0_ = -1.0;
  for (int j = 0; j < M_; j++)
    for (int k = 0; k < N_; k++) {
      double dN = (double) (N_ - 1);
      double dk = (double) k;
      double gamma_jk = 1.0 / (((1.0 - q_) / ((1 / time_to_progression_to_severity_[j][k]))) + (q_ * tau_1_));
      double dur = (zI_ / gamma_jk) +
                   (w_[j][k] * (1.0 - q_) * (zV_ * (1.0 - h_) + zH_ * h_) / (1 / time_to_progression_to_death_[j][k])) +
                   (zQ_ * q_ * tau_1_ + q_ * zQ_ * w_[j][k] / (1 / time_to_progression_to_severity_[j][k]));

      double R0 = alpha_[j] * beta_[k] * dur;


      if (R0 > G_MAX_R0_) G_MAX_R0_ = R0;
    }

  if (R0max_ > 0.0) {
    beta_a0_ *= (R0max_ / G_MAX_R0_);
    G_MAX_R0_ = R0max_;
  }

}