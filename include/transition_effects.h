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

class TransitionEffects {
 public:
  TransitionEffects(std::string stack_input_symbols, const std::string& current_state, std::string destiny_state, unsigned identifier) 
      :  identifier_{identifier}, destiny_state_{destiny_state}, stack_input_symbols_{stack_input_symbols} {}

  bool operator<(const TransitionEffects& other_transition_effects) const;
 private:
  const std::string destiny_state_;
  const std::string stack_input_symbols_;
  unsigned identifier_;
};