// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_loader.cc: implementation file.
// Contains the implementation of the PushdownAutomatonLoader class.

#include "../../include/pushdown_automaton_load/pushdown_automaton_loader.h"

PushdownAutomaton PushdownAutomatonLoader::LoadPushdownAutomaton() const {
  return load_strategy_->LoadPushdownAutomaton(file_path_);
}
