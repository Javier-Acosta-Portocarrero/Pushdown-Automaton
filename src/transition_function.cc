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
 * @brief Retrieves the possible transitions based on the given instantaneous description.
 * @param requirements The instantaneous description containing the current state, stack top, and entry symbol.
 * @return A set of possible TransitionEffects that can be applied from the given requirements.
 */
std::set<TransitionEffects> TransitionFunction::GetPossibleTransitions(const InstantaneousDescription& requirements) const {
  auto state_iterator = inner_transition_table_.find(requirements.state_);
  if (state_iterator == inner_transition_table_.end()) {
    return {};
  }
  auto stack_top_iterator = state_iterator->second.find(requirements.stack_top_);
  if (stack_top_iterator == inner_transition_table_.at(requirements.state_).end()) {
    return {};
  }

  std::set<TransitionEffects> possible_transitions = {};
  // Recordatory: I am using '.' as an equivalent to epslon
  if (requirements.entry_symbol_ != '.') {
    auto entry_symbol_range = stack_top_iterator->second.equal_range(requirements.entry_symbol_);
    for (auto iterator = entry_symbol_range.first; iterator != entry_symbol_range.second; ++iterator) {
      possible_transitions.insert(iterator->second);
    }
  }
  auto epsilon_range = stack_top_iterator->second.equal_range('.');
  for (auto iterator = epsilon_range.first; iterator != epsilon_range.second; ++iterator) {
    TransitionEffects transition = iterator->second;
    // Needed to know if the entry string has to advance or not
    transition.SetNotConsumedSymbol();
    possible_transitions.insert(transition);
  }

  return possible_transitions;
}

/**
 * @brief Adds a new transition to the transition function based on the given instantaneous description and transition effects.
 * @param requirements The instantaneous description containing the current state, stack top, and entry symbol.
 * @param output The TransitionEffects that define the effects of the transition.
 */
void TransitionFunction::AddNewTransition(const InstantaneousDescription& requirements, const TransitionEffects& output) {
  inner_transition_table_[requirements.state_][requirements.stack_top_].insert(std::make_pair(requirements.entry_symbol_, output)); 
}