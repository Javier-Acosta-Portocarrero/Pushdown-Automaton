// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 20/09/2026
// File transition.h: declaration file.
// Contains the declaration of the Transition class.

#include <string>

using Symbol = char;

class Transition {
 public:
  Transition(Symbol entry_symbol, Symbol stack_top_symbol, std::string stack_input_symbols,
    const std::string& current_state, std::string destiny_state, unsigned identifier) 
      : entry_symbol_{entry_symbol}, stack_top_symbol_{stack_top_symbol}, identifier_{identifier},
        current_state_{current_state}, destiny_state_{destiny_state}, stack_input_symbols_{stack_input_symbols} {}

  bool Match(const InstantaneousDescription& automaton_description) const;
 private:
  // Conditions
  const Symbol entry_symbol_;
  const Symbol stack_top_symbol_;
  const std::string current_state_;
  // Effects
  const std::string destiny_state_;
  const std::string stack_input_symbols_;
  unsigned identifier_;
};