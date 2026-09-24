// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_loader.h: declaration file.
// Contains the declaration of the PushdownAutomatonLoader class.

#ifndef PUSHDOWN_AUTOMATON_LOADER_H
#define PUSHDOWN_AUTOMATON_LOADER_H

#include "../pushdown_automaton.h"
#include "pushdown_automaton_loader_strategy.h"

class PushdownAutomatonLoader {
 public:
  PushdownAutomatonLoader(PushdownAutomatonLoaderStrategy* load_strategy, const std::string& file_path = "") 
      : load_strategy_{load_strategy}, file_path_{file_path} {}

  void SetFilePath(std::string new_path) { file_path_ = new_path;}
  PushdownAutomaton LoadPushdownAutomaton() const;
 private:
  PushdownAutomatonLoaderStrategy* load_strategy_ = nullptr;
  std::string file_path_;
};

#endif