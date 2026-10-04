// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main_functions.cc: implementation file.
// Contains the implementation of the main program auxiliary functions.

#include "../include/main_functions.h"
#include "../include/exceptions/input_exception.h"

#include <fstream>
#include <iostream>

/**
 * 
 */
void ReadProgramArguments(int argc, char* argv[], std::string& config_file, std::string& input_file, bool& trace_active, bool& parameter_error) {
  bool trace_option_found = false;
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    if (argument == "-config") {
      if (i + 1 >= argc) {
        parameter_error = true;
        throw InputException("Missing file after -config.");
      }
      config_file = argv[++i];

    } else if (argument == "-trace") {
      if (i + 1 >= argc) {
        parameter_error = true;
        throw InputException("Missing value after -trace.");
      }
      const std::string trace_value = argv[++i];
      if (trace_value == "y") {
        trace_active = true;
      } else if (trace_value == "n") {
        trace_active = false;
      } else {
        parameter_error = true;
        throw InputException("Trace value must be 'y' or 'n'.");
      }
      trace_option_found = true;

    } else if (argument == "-in") {
      if (i + 1 >= argc) {
        parameter_error = true;
        throw InputException("Missing file after -in.");
      }
      input_file = argv[++i];

    } else {
      parameter_error = true;
      throw InputException("Unknown option '" + argument + "'.");
    }
  }
  if (config_file.empty()) {
    parameter_error = true;
    throw InputException("Missing -config option.");
  }
  if (!trace_option_found) {
    parameter_error = true;
    throw InputException("Missing -trace option.");
  }
}

/**
 * 
 */
void ExecuteInputFile(PushdownAutomaton& automaton, const std::string& input_file) {
  std::ifstream words_file{input_file};
  if (!words_file.is_open()) {
    throw InputException("Could not open input file '" + input_file + "'.");
  }
  std::string input_word;
  while (std::getline(words_file, input_word)) {
    if (!input_word.empty() && input_word.back() == '\r') {
      input_word.pop_back();
    }
    std::cout << input_word << ": " << (automaton.AcceptsWord(input_word) ? "\nAccepted" : "\nRejected") << std::endl;
  }
}

/**
 * 
 */
void ExecuteKeyboardInput(PushdownAutomaton& automaton) {
  std::string input_word;
  while (true) {
    std::cout << "\nInput word (type exit to finish): ";
    std::cin >> input_word;
    if (input_word == "exit") {
      break;
    }
    std::cout << (automaton.AcceptsWord(input_word) ? "\nAccepted" : "\nRejected") << std::endl;
  }
}