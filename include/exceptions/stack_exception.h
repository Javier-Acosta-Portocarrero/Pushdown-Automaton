// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 01/10/2026
// File stack_exception.h: declaration file.
// Contains the declaration of the StackException class.

#ifndef STACK_EXCEPTION_H
#define STACK_EXCEPTION_H

#include <stdexcept>

class StackException : public std::runtime_error {
 public:
  explicit StackException(const std::string& message) : std::runtime_error(message) {}
};

#endif