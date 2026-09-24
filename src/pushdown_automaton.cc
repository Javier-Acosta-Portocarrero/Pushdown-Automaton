// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton.cc: implementation file.
// Contains the implementation of the PushdownAutomaton class.

#include "../include/pushdown_automaton.h"

#include <iostream>
#include <iomanip>  // Needed for std::setw

/**
 * 
 */
bool PushdownAutomaton::AcceptsWord(const std::string& input_word) {
  if (trace_active_) {
    std::cout << std::setw(5) << "\n\nState" << "Input String" << "Stack" << "Transitions\n";
  }
  InputString initial_string{input_word};
  std::stack<Symbol> initial_stack = {};
  initial_stack.push(start_stack_symbol_);

  return RecursiveChecking(start_state_, initial_stack, initial_string);
}
   
/**
 * 
 */
bool PushdownAutomaton::RecursiveChecking(const std::string& current_state, std::stack<Symbol>& current_stack, const InputString& current_string) const {
  InstantaneousDescription current_instantaneous_description_(current_state, current_stack.top(), current_string.GetCurrentSymbol());
  if (trace_active_) {
    std::cout << std::setw(5) << current_state;
    const std::string& tmp_input_word = current_string.GetInputWordReference();
    std::cout << std::setw(5) << tmp_input_word.substr(current_string.GetCurrentPositionIndex(), tmp_input_word.size() - 1);
    // Need to copy the stack so I can show its content.
    if (current_stack.empty()) {
      std::cout << std::setw(5) << '.' << "-";
    } else {
      std::stack tmp = current_stack;
      std::string stack_content = "";
      while (!tmp.empty()) {
        stack_content += tmp.top();
        tmp.pop();
      }
      std::cout << std::setw(5) << stack_content;
    }
  }

  // The acceptance criterion of this pushdown automaton is having an empty stack and have consumed the whole input string.
  if (current_stack.empty()) {
    if (!current_string.IsEmpty()) {
      return false;
    }
    return true;
  }

  std::set<TransitionEffects> possible_transitions = inner_transition_function_.GetPossibleTransitions(current_instantaneous_description_);
  if (trace_active_) {
    for (const TransitionEffects& transition : possible_transitions) {
      std::cout << std::setw(1) << transition.GetIdentifier();
    }
    std::cout << std::endl;
  }

  current_stack.pop();
  for (const TransitionEffects& transition : possible_transitions) {
    const std::string& next_state = transition.GetDestinyState();

    std::stack<Symbol> new_branch_stack = current_stack;
    const std::string& new_stack_symbols = transition.GetStackInputSymbols();
    for (size_t i = new_stack_symbols.size() - 1; i >= 0; --i) {
      new_branch_stack.push(new_stack_symbols[i]);    
    }

    InputString updated_input_string = current_string.GewStringCopyWithReference();
    if (transition.ConsumesEntrySymbol()) {
      updated_input_string.AdvanceString();
    }

    if (RecursiveChecking(next_state, new_branch_stack, updated_input_string)) {
      return true;    
    }
  }

  return false;
}
