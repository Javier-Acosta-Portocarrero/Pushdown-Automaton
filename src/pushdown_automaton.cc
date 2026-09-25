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
 * @brief Checks if the pushdown automaton accepts the given input word.
 * @param input_word Input word to check.
 * @return true if the automaton accepts the word or false if not.
 */
bool PushdownAutomaton::AcceptsWord(const std::string& input_word) {
  unsigned output_width = input_word.size() + 2 < 18 ? 18 : input_word.size() + 2;
  if (trace_active_) {
    std::cout << std::left << "\n" << std::setw(output_width) << "State" << std::setw(output_width) << "Input String"
              << std::setw(output_width) << "Stack" << std::setw(output_width) << "Transitions" << std::endl;
  }
  InputString initial_string{input_word, input_alphabet_};
  Stack initial_stack{stack_alphabet_, start_stack_symbol_};

  return RecursiveChecking(start_state_, initial_stack, initial_string, output_width);
}
   
/**
 * @brief Recursively checks if the pushdown automaton can accept the given input, that happens when the 
 *        stack is empty and the entire input string has been consumed.
 * @param current_state The current state of the automaton.
 * @param current_stack The current stack of the automaton.
 * @param current_string The current input string.
 * @param output_width The width of the output columns.
 * @return true if the automaton can accept the input or false if not.
 */
bool PushdownAutomaton::RecursiveChecking(const std::string& current_state, Stack& current_stack, const InputString& current_string, unsigned output_width) const {
  if (trace_active_) {
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
  // The acceptance criterion of this pushdown automaton is having an empty stack and have consumed the whole input string.
  if (current_stack.IsEmpty()) {
    return current_string.IsEmpty();
  }

  InstantaneousDescription current_instantaneous_description_(current_state, current_stack.Top(), current_string.GetCurrentSymbol());
  std::set<TransitionEffects> possible_transitions = inner_transition_function_.GetPossibleTransitions(current_instantaneous_description_);
  // Trace part of the possible transitions, printed by id and separated by 1 space
  if (trace_active_) {
    std::string transitions_id = "";
    for (const TransitionEffects& transition : possible_transitions) {
      transitions_id += std::to_string(transition.GetIdentifier()) + ' ';
    }
    if (transitions_id == "") {
      transitions_id = "-";
    }
    std::cout << std::setw(output_width) << transitions_id << std::endl;
  }

  current_stack.Pop();
  for (const TransitionEffects& transition : possible_transitions) {
    const std::string& next_state = transition.GetDestinyState();
    Stack new_branch_stack = current_stack.GetStackCopy();
    const std::string& new_stack_symbols = transition.GetStackInputSymbols();
    // I do it in this order because the first symbol of the string must be the top of the stack
    for (int i = new_stack_symbols.size() - 1; i >= 0; --i) {
      new_branch_stack.Push(new_stack_symbols[i]);    
    }
    InputString updated_input_string = current_string.GetStringCopyWithReference();
    if (transition.ConsumesEntrySymbol()) {
      updated_input_string.AdvanceString();
    }

    if (RecursiveChecking(next_state, new_branch_stack, updated_input_string, output_width)) {
      return true;
    }
  }

  return false;
}
