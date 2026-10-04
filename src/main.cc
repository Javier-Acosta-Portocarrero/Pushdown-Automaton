// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main.cc: main program file.
// Contains the main function of the pushdown automaton simulator.

#include "../include/pushdown_automaton_load/pushdown_automaton_loader.h"
#include "../include/pushdown_automaton_load/pushdown_automaton_loader_plain_text_strategy.h"
#include "../include/main_functions.h"

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
    ReadProgramArguments(argc, argv, config_file, input_file, trace_active, parameter_error);

    std::cout << "This empty-stack-focused pushdown automaton has a DFS behaviour and executes the transitions.\n"
              << "in ascending order by ID. The transitions that appear earlier in the input file have a smaller ID.\n\n";

    PushdownAutomatonLoaderPlainTextStrategy plain_text_strategy;
    PushdownAutomatonLoader loader{&plain_text_strategy, config_file};
    PushdownAutomaton automaton = loader.LoadPushdownAutomaton();
    automaton.SetTraceActive(trace_active);

    if (!input_file.empty()) {
      ExecuteInputFile(automaton, input_file);
    } else {
      ExecuteKeyboardInput(automaton);
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