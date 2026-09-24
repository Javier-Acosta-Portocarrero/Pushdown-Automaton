// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File main.cc: main program file.
// Contains the main function of the pushdown automaton simulator.

#include "../include/pushdown_automaton_load/pushdown_automaton_loader.h"
#include "../include/pushdown_automaton_load/pushdown_automaton_loader_plain_text_strategy.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief Main function of the pushdown automaton simulator.
 */
int main(int argc, char* argv[]) {
  bool parameter_error = false;

  try {
    std::string config_file;
    std::string input_file;
    bool trace_active = false;
    bool trace_option_found = false;
    for (int i = 1; i < argc; ++i) {
      const std::string argument = argv[i];
      if (argument == "-config") {
        if (i + 1 >= argc) {
          parameter_error = true;
          throw std::runtime_error("Missing file after -config.");
        }
        config_file = argv[++i];

      } else if (argument == "-trace") {
        if (i + 1 >= argc) {
          parameter_error = true;
          throw std::runtime_error("Missing value after -trace.");
        }
        const std::string trace_value = argv[++i];
        if (trace_value == "y") {
          trace_active = true;
        } else if (trace_value == "n") {
          trace_active = false;
        } else {
          parameter_error = true;
          throw std::runtime_error("Trace value must be 'y' or 'n'.");
        }
        trace_option_found = true;

      } else if (argument == "-in") {
        if (i + 1 >= argc) {
          parameter_error = true;
          throw std::runtime_error("Missing file after -in.");
        }
        input_file = argv[++i];

      } else {
        parameter_error = true;
        throw std::runtime_error("Unknown option '" + argument + "'.");
      }
    }
    if (config_file.empty()) {
      parameter_error = true;
      throw std::runtime_error("Missing -config option.");
    }
    if (!trace_option_found) {
      parameter_error = true;
      throw std::runtime_error("Missing -trace option.");
    }

    PushdownAutomatonLoaderPlainTextStrategy plain_text_strategy;
    PushdownAutomatonLoader loader{&plain_text_strategy, config_file};
    PushdownAutomaton automaton = loader.LoadPushdownAutomaton();
    automaton.SetTraceActive(trace_active);
    if (!input_file.empty()) {
      std::ifstream words_file{input_file};
      if (!words_file.is_open()) {
        throw std::runtime_error("Could not open input file '" + input_file + "'.");
      }
      std::string input_word;
      while (std::getline(words_file, input_word)) {
        if (!input_word.empty() && input_word.back() == '\r') {
          input_word.pop_back();
        }
        std::cout << input_word << ": " << (automaton.AcceptsWord(input_word) ? "Accepted" : "Rejected") << std::endl;
      }

    } else {
      std::string input_word;
      while (true) {
        std::cout << "\nInput word (type exit to finish): ";
        std::cin >> input_word;
        if (input_word == "exit") {
          break;
        }
        std::cout << (automaton.AcceptsWord(input_word) ? "Accepted" : "Rejected") << std::endl;
      }
    }
    return 0;

  } catch (const std::exception& exception) {
    std::cerr << "Error: " << exception.what() << std::endl;
    if (parameter_error) {
      std::cerr << "\nUsage:\n";
      std::cerr << "  " << argv[0] << " -config <file> -trace <y|n> [-in <file>]\n";
    }
    return 1;
  }
}