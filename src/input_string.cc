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

#include <stdexcept>

/**
 * @brief Default constructor for the InputString class.
 */
InputString::InputString(const std::set<Symbol>& input_alphabet) : input_alphabet_{input_alphabet} {
  inner_string_ = new std::string("");
  current_position_ = 0;
}

/**
 * @brief Constructor for the InputString class with an input word.
 * @param input_word Input word to be processed.
 * @param input_alphabet Set of symbols that form the input alphabet.
 * @param current_position Current position in the input word (default is 0).
 */
InputString::InputString(const std::string& input_word, const std::set<Symbol>& input_alphabet, unsigned current_position) 
    : inner_string_{&input_word}, current_position_{current_position}, input_alphabet_{input_alphabet} {
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw std::runtime_error("The input word contains symbols that are not in the input alphabet.");
  }
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
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw std::runtime_error("The input word contains symbols that are not in the input alphabet.");
  }
  inner_string_ = &input_word;
  current_position_ = 0;
}

/**
 * @brief Creates a copy of the InputString object with the same reference to the input word.
 * @return A copy of the InputString object.
 */
InputString InputString::GetStringCopyWithReference() const {
  return InputString(*inner_string_, input_alphabet_, current_position_);
}

/**
 * @brief Checks if the entire input word is composed of symbols from the input alphabet.
 * @param input_word Input word to be checked.
 * @return true if the input word is valid, false otherwise.
 */
bool InputString::CheckIfWholeInputWordIsInAlphabet(const std::string& input_word) const {
  for (const Symbol& symbol : input_word) {
    if (!input_alphabet_.contains(symbol)) {
      return false;
    }
  }
  return true;
}