// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_loader_plain_text_strategy.h: declaration file.
// Contains the declaration of the PushdownAutomatonLoaderPlainTextStrategy class.

#ifndef PUSHDOWN_AUTOMATON_LOADER_PLAIN_TEXT_STRATEGY_H
#define PUSHDOWN_AUTOMATON_LOADER_PLAIN_TEXT_STRATEGY_H

#include "pushdown_automaton_loader_strategy.h"

class PushdownAutomatonLoaderPlainTextStrategy : public PushdownAutomatonLoaderStrategy {
 public:
  PushdownAutomatonLoaderPlainTextStrategy() = default;
  ~PushdownAutomatonLoaderPlainTextStrategy() = default;

  PushdownAutomaton LoadPushdownAutomaton(const std::string& file_path) const override;
 private:
  std::string GetNextContentLine(std::ifstream& input_file, unsigned& line_number, const std::string& expected_content) const;
  std::string RemoveCommentsAndWhitespace(const std::string& line) const;
  std::set<std::string> ReadStates(const std::string& line, unsigned line_number) const;
  std::set<Symbol> ReadAlphabet(const std::string& line, unsigned line_number, const std::string& alphabet_name) const;
  std::string ReadSingleElement(const std::string& line, unsigned line_number, const std::string& element_name) const;

  void ReadTransition(const std::string& line, unsigned line_number, unsigned transition_identifier,
      const std::set<std::string>& automaton_states, const std::set<Symbol>& input_alphabet, 
      const std::set<Symbol>& stack_alphabet,TransitionFunction& transition_function) const;
};

#endif 