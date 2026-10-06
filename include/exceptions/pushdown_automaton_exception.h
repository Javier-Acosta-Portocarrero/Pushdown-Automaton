// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 06/10/2026
// File pushdown_automaton_exception.h: declaration file.
// Contains the declaration of the PushdownAutomatonException class.

#ifndef PUSHDOWN_AUTOMATON_EXCEPTION_H
#define PUSHDOWN_AUTOMATON_EXCEPTION_H

#include <stdexcept>

class PushdownAutomatonException : public std::runtime_error {
 public:
  explicit PushdownAutomatonException(const std::string& message) : std::runtime_error(message) {}
};

#endif