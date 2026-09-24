// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 20/09/2026
// File input_string.cc: implementation file.
// Contains the implementation of the InputString class.

#include "../include/input_string.h"

/**
 * 
 */
InputString::InputString() {
  inner_string_ = new std::string("");
}

/**
 * @brief Returns the current input symbol.
 *
 * @return The current symbol, or '.' if the input string is empty (epsilon equivalent).
 */
Symbol InputString::GetCurrentSymbol() const {
  // Im using '.' as the equivalent to epsilon in a classic pushdown automaton.
  return inner_string_ == nullptr || IsEmpty()? '.' : (*inner_string_)[current_position_];
}

/**
 * @brief Advances to the next symbol of the input string.
 */
void InputString::AdvanceString() {
  if (inner_string_ != nullptr && current_position_ < inner_string_->length()) {
    ++current_position_;
  }
}

/**
 * @brief Checks if the input string has been completely processed.
 *
 * @return true if the input string is empty or fully processed or fale if not.
 */
bool InputString::IsEmpty() const {
  return inner_string_ == nullptr || current_position_ >= inner_string_->length();
}

/**
 * @brief Sets a new input word.
 *
 * @param input_word New input word.
 */
void InputString::IntroduceNewInputWordByReference(const std::string& input_word) {
  inner_string_ = &input_word;
  current_position_ = 0;
}

/**
 * 
 */
InputString InputString::GewStringCopyWithReference() const {
  return InputString(*inner_string_, current_position_);
}
