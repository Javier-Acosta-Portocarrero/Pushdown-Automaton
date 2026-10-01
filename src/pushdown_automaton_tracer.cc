// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_tracer.cc: implementation file.
// Contains the implementation of the PushdownAutomatonTracer class.

#include "../include/pushdown_automaton_tracer.h"

#include <iostream>
#include <iomanip>  // Needed for std::setw

/**
 * @brief Prints the header of the pushdown automaton trace.
 * @param output_width The width of the output columns.
 */
void PushdownAutomatonTracer::PrintHeader(unsigned output_width) const {
  std::cout << std::left << "\n" << std::setw(output_width) << "State" << std::setw(output_width) << "Input String"
            << std::setw(output_width) << "Stack" << std::setw(output_width) << "Transitions" << std::endl;
}

/**
 * @brief Prints the current configuration of the pushdown automaton.
 * @param current_state The current state of the automaton.
 * @param current_stack The current stack of the automaton.
 * @param current_string The current input string.
 * @param output_width The width of the output columns.
 */
void PushdownAutomatonTracer::PrintCurrentConfiguration(const std::string& current_state, Stack& current_stack,
                                                       const InputString& current_string, unsigned output_width) const {
  std::cout << std::setw(output_width) << current_state;
  if (current_string.IsEmpty()) {
    std::cout << std::setw(output_width) << '.';
  } else {
    const std::string& tmp_input_word = current_string.GetInputWordReference();
    std::cout << std::setw(output_width) << tmp_input_word.substr(current_string.GetCurrentPositionIndex());
  }
  std::cout << std::setw(output_width) << current_stack.GetStackContentAsString();
  if (current_stack.IsEmpty()) {  // If the stack is empty, there cant be any possible transitions
    std::cout << std::setw(output_width) << '-' << std::endl;
  }
}

/**
 * @brief Prints the possible transitions of the pushdown automaton.
 * @param possible_transitions The possible transitions from the current instantaneous description.
 * @param output_width The width of the output columns.
 */
void PushdownAutomatonTracer::PrintPossibleTransitions(const std::set<TransitionEffects>& possible_transitions,
                                                       unsigned output_width) const {
  
  // They are printed by id and separated by 1 space                                          
  std::string transitions_id = "";
  for (const TransitionEffects& transition : possible_transitions) {
    transitions_id += std::to_string(transition.GetIdentifier()) + ' ';
  }
  if (transitions_id == "") {
    transitions_id = "-";
  }
  std::cout << std::setw(output_width) << transitions_id << std::endl;
}