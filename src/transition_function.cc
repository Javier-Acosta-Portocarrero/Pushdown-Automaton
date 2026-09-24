// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File transition_function.cc: implementation file.
// Contains the implementation of the TransitionFunction class.

#include "../include/transition_function.h"


/**
 * 
 */
std::set<TransitionEffects> TransitionFunction::GetPossibleTransitions(const std::string& state, Symbol stack_top, Symbol entry_symbol) const {
  auto state_iterator = inner_transition_table_.find(state);
  if (state_iterator == inner_transition_table_.end()) {
    return {};
  }

  auto stack_top_iterator = state_iterator->second.find(stack_top);
  if (stack_top_iterator == inner_transition_table_.at(state).end()) {
    return {};
  }

  std::set<TransitionEffects> possible_transitions = {};
  auto entry_symbol_range = stack_top_iterator->second.equal_range(entry_symbol);
  for (auto iterator = entry_symbol_range.first; iterator != entry_symbol_range.second; ++iterator) {
    possible_transitions.insert(iterator->second);
  }
  // Recordatory: I am are using '.' as an equivalent to epslin.
  auto epsilon_range = stack_top_iterator->second.equal_range('.');
  for (auto iterator = epsilon_range.first; iterator != epsilon_range.second; ++iterator) {
    possible_transitions.insert(iterator->second);
  }

  return possible_transitions;
}

/**
 * 
 */
void TransitionFunction::AddNewTransition(const InstantaneousDescription& requirements, const TransitionEffects& output) {
  inner_transition_table_[requirements.state_][requirements.stack_top_].insert(std::make_pair(requirements.entry_symbol_, output)); 
}