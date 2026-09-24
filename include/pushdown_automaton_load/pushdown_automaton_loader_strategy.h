// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_strategy.h: declaration file.
// Contains the declaration of the PushdownAutomatonLoaderStrategy class.

#ifndef PUSHDOWN_AUTOMATON_LOADER_STRATEGY_H
#define PUSHDOWN_AUTOMATON_LOADER_STRATEGY_H

#include "../pushdown_automaton.h"

class PushdownAutomatonLoaderStrategy {
 public:
  virtual ~PushdownAutomatonLoaderStrategy() = default;

  virtual PushdownAutomaton LoadPushdownAutomaton(const std::string& file_path) const = 0;
};

#endif