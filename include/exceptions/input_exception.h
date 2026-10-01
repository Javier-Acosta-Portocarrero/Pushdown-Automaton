// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 01/10/2026
// File input_exception.h: declaration file.
// Contains the declaration of the InputException class.

#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include <stdexcept>

class InputException : public std::runtime_error {
 public:
  explicit InputException(const std::string& message) : std::runtime_error(message) {}
};

#endif