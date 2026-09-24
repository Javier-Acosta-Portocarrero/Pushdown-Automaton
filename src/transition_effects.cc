// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 23/09/2026
// File transition_effects.cc: implementation file.
// Contains the implementation of the TransitionEffects class.

#include "../include/transition_effects.h"

/**
 * @brief Compares two TransitionEffects objects based on their identifiers.
 * @param transition_to_compare The TransitionEffects object to compare with.
 * @return true if the identifier of this object is less than the identifier of the other object or false if not.
 */
bool TransitionEffects::operator<(const TransitionEffects& transition_to_compare) const {
  return identifier_ < transition_to_compare.identifier_;
}
