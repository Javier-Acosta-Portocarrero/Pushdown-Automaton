// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 20/09/2026
// File input_string.h: declaration file.
// Contains the declaration of the InputString class.

#include <string>

using Symbol = char;

class InputString {
 public:
  InputString();
  InputString(const std::string& input_word, unsigned current_position = 0) 
      : inner_string_{&input_word}, current_position_{current_position} {}

  Symbol GetCurrentSymbol() const;
  const std::string& GetInputWordReference() const { return *inner_string_;}
  InputString GewStringCopyWithReference() const;
  unsigned GetCurrentPositionIndex() const { return current_position_;}

  void AdvanceString();
  bool IsEmpty() const;

  void IntroduceNewInputWordByReference(const std::string& input_word);
 private:
  const std::string* inner_string_ = nullptr;
  unsigned current_position_ = 0;
};