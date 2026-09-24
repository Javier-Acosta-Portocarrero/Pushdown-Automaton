// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 20/09/2026
// File instantaneous_description.h: declaration file.
// Contains the declaration of the InstantaneousDescription struct.

#include <string>

using Symbol = char;

struct InstantaneousDescription {
  InstantaneousDescription(const std::string& state, Symbol stack_top, Symbol entry_symbol) 
      : state_{state}, stack_top_{stack_top}, entry_symbol_{entry_symbol} {}
  
  const std::string state_;
  const Symbol stack_top_;
  const Symbol entry_symbol_;  
};