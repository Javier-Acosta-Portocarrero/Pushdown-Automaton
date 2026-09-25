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

#ifndef INPUT_STRING_H
#define INPUT_STRING_H

#include <string>
#include <set>

using Symbol = char;

class InputString {
 public:
  InputString(const std::set<Symbol>& input_alphabet);
  InputString(const std::string& input_word, const std::set<Symbol>& input_alphabet, unsigned current_position = 0);

  Symbol GetCurrentSymbol() const;
  const std::string& GetInputWordReference() const { return *inner_string_;}
  InputString GetStringCopyWithReference() const;
  unsigned GetCurrentPositionIndex() const { return current_position_;}

  void AdvanceString();
  bool IsEmpty() const;

  void IntroduceNewInputWordByReference(const std::string& input_word);
 private:
  const std::string* inner_string_ = nullptr;
  unsigned current_position_ = 0;
  // I use a reference because a lot of InputString objects will be created during the execution of the program (it is recursive), 
  // and I don't want to copy the input alphabet every time.
  const std::set<Symbol>& input_alphabet_;

  bool CheckIfWholeInputWordIsInAlphabet(const std::string& input_word) const;
};

#endif