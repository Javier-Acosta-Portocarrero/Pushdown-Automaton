// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 20/09/2026
// File transition_function.h: declaration file.
// Contains the declaration of the TransitionFunction class.

#include "transition_effects.h"

#include <map>
#include <set>

using Symbol = char;

class TransitionFunction {
 public:
  TransitionFunction() = default;
  TransitionFunction(const std::map<std::string, std::map<Symbol, std::multimap<Symbol, TransitionEffects>>>& transition_table) 
      :  inner_transition_table_{transition_table} {}

  std::set<TransitionEffects> GetPossibleTransitions(const std::string& state, Symbol stack_top, Symbol entry_symbol) const;
  void AddNewTransition(const std::string& state, Symbol stack_top, Symbol entry_symbol, const TransitionEffects& output);
 private:
  std::map<std::string, std::map<Symbol, std::multimap<Symbol, TransitionEffects>>> inner_transition_table_;
};