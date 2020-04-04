/* 
 * File:   main.cpp
 * Author: merlin
 *
 * Created on May 20, 2012, 2:15 PM
 */

#include <cstdlib>
#include "Model.h"
#include "ConsoleReporter.h"
#include "FarmReporter.h"
#include "FarmReporter2.h"
#include "FarmReporter3.h"
#include "FarmReporter4.h"
#include "ezOptionParser.hpp"
#include "Config.h"

using namespace std;

/*
 * 
 */

using namespace ez;

void CreateOptionParser(ezOptionParser &opt);

int main(int argc, const char* argv[]) {

  Model influenzaModel;

  ezOptionParser opt;
  CreateOptionParser(opt);
  opt.parse(argc, argv);

  if (opt.isSet("-h")) {
    std::string usage;
    int layout;
    opt.get("-h")->getInt(layout);
    switch (layout) {
      case 0:
        opt.getUsage(usage, 80, ezOptionParser::ALIGN);
        break;
      case 1:
        opt.getUsage(usage, 80, ezOptionParser::INTERLEAVE);
        break;
      case 2:
        opt.getUsage(usage, 80, ezOptionParser::STAGGER);
        break;
    }
    std::cout << usage;
    return 1;
  }

  std::string config_file_name = "config.yml";
  if (opt.isSet("-c")) {

    opt.get("-c")->getString(config_file_name);
  }

  std::string override_file_name;
  int override_pos = 0;
  if (opt.isSet("-o")) {
    std::string override_param;
    opt.get("-o")->getString(override_param);
    override_file_name = override_param;

    opt.get("-p")->getString(override_param);
    override_pos = atoi(override_param.c_str());
  }

  unsigned int seed = -1;
  if (opt.isSet("-s")) {
    opt.get("-s")->getInt(seed);
  }

  //initialize population
  influenzaModel.Initialize(seed, config_file_name, override_file_name, override_pos);


  //initialize first case
  influenzaModel.InitiallizeFirstCase();


  if (opt.isSet("-f")) {
    int farmOutput = 0;
    opt.get("-f")->getInt(farmOutput);
    if (farmOutput == 1) {
      influenzaModel.RegisterReporter(new FarmReporter());
    } else if (farmOutput == 2) {
      influenzaModel.RegisterReporter(new FarmReporter2());
    } else if (farmOutput == 3) {
      influenzaModel.RegisterReporter(new FarmReporter3());
    } else if (farmOutput == 4) {
      influenzaModel.RegisterReporter(new FarmReporter4());
    }

  } else {
    //set console Reporter
    auto* reporter = new ConsoleReporter();
    influenzaModel.RegisterReporter(reporter);

  }

  influenzaModel.Run();

  influenzaModel.Release();

  return 0;

}

void CreateOptionParser(ezOptionParser &opt) {
  opt.overview = "Individual-based simulation for influenza.";
  opt.syntax = "ibmflu [OPTIONS]";
  opt.example = "ibmflu -h\n\n";
  opt.footer = "ibmflu v0.9.0 Copyright (C) 2012 OUCRU.\n";

  opt.add(
    "0", // Default.
    0, // Required?
    1, // Number of args expected.
    0, // Delimiter if expecting multiple args.
    "Display usage instructions.\nThere is a choice of three different layouts for description alignment. Your choice can be any one of the following to suit your style:\n\n0 - align (default)\n1 - interleave\n2 - stagger", // Help description.
    "-h", // Flag token.
    "-help", // Flag token.
    "--help", // Flag token.
    "--usage" // Flag token.
  );
  opt.add(
    "1", // Default.
    0, // Required?
    1, // Number of args expected.
    ' ', // Delimiter if expecting multiple args.
    "Run the simulation with farm output.", // Help description.
    "-f", // Flag token.
    "-farm", // Flag token.
    "--farm" // Flag token.
  );

  opt.add(
    "config.yml", // Default.
    0, // Required?
    1, // Number of args expected.
    0, // Delimiter if expecting multiple args.
    "The config file (YAML format).", // Help description.
    "-c", // Flag token.
    "-i", // stand for input
    "-cfg", // Flag token.
    "--config" // Flag token.
  );

  opt.add("override.txt",
          0,
          1,
          0,
          "Provide file name and line number to overwrite input parameters",
          "-o",
          "--override"
  );

  opt.add("1",
          0,
          1,
          0,
          "Provide line number to overwrite input parameters",
          "-p",
          "--pos"
  );

  opt.add("-1",
          0,
          1,
          0,
          "Seed number for random generator",
          "-s",
          "--seed"
  );
}