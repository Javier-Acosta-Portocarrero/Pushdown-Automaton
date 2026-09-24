// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton.h: declaration file.
// Contains the declaration of the PushdownAutomaton class.

#include "transition_function.h"
#include "input_string.h"

using Symbol = char;

// Empty stack version of a pushdown automaton
class PushdownAutomaton {
 public:
  
 private:
  const InputString original_input_string_;
  const TransitionFunction inner_transition_function_;
  const std::set<Symbol> input_alphabet_;
  const std::set<Symbol> stack_alphabet_;
  const Symbol start_stack_symbol_;
  const std::set<std::string> automaton_states_;
  const std::string start_state_;
};