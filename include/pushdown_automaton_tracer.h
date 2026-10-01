// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 01/10/2026
// File pushdown_automaton_tracer.h: declaration file.
// Contains the declaration of the PushdownAutomatonTracer class.

#ifndef PUSHDOWN_AUTOMATON_TRACER_H
#define PUSHDOWN_AUTOMATON_TRACER_H

#include "transition_function.h"
#include "input_string.h"
#include "stack.h"

class PushdownAutomatonTracer {
 public:
  void PrintHeader(unsigned output_width) const;
  void PrintCurrentConfiguration(const std::string& current_state, Stack& current_stack,
    const InputString& current_string, unsigned output_width) const;
  void PrintPossibleTransitions(const std::set<TransitionEffects>& possible_transitions, unsigned output_width) const;
};

#endif