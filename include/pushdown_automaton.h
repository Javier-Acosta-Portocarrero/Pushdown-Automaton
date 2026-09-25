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

#ifndef PUSHDOWN_AUTOMATON_H
#define PUSHDOWN_AUTOMATON_H

#include "transition_function.h"
#include "input_string.h"
#include "instantaneous_description.h"

#include <stack>

using Symbol = char;

// Empty stack version of a pushdown automaton
class PushdownAutomaton {
 public:
  PushdownAutomaton(const InputString& original_input_string, const TransitionFunction& inner_transition_function,
    const std::set<Symbol>& input_alphabet, const std::set<Symbol>& stack_alphabet,
    const Symbol& start_stack_symbol, const std::set<std::string>& automaton_states,
    const std::string& start_state, bool trace_active = false) 
      : inner_transition_function_{inner_transition_function}, 
      input_alphabet_{input_alphabet}, stack_alphabet_{stack_alphabet}, start_stack_symbol_{start_stack_symbol},
      automaton_states_{automaton_states}, start_state_{start_state}, trace_active_{trace_active} {}

  bool AcceptsWord(const std::string& input_word);
  void SetTraceActive(bool trace_flag) { trace_active_ = trace_flag;}
      
 private:
  const TransitionFunction inner_transition_function_;
  const std::set<Symbol> input_alphabet_;
  // Doesn't contain a stack or input string because of the recursive nature of this program,
  // only has the necessary data to build all the stacks and input string during the execution
  const std::set<Symbol> stack_alphabet_;
  const Symbol start_stack_symbol_;
  const std::set<std::string> automaton_states_;
  const std::string start_state_;

  bool trace_active_;

  bool RecursiveChecking(const std::string& current_state, std::stack<Symbol>& current_stack, const InputString& current_string, unsigned output_width) const;
};

#endif