// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 25/09/2026
// File stack.h: declaration file.
// Contains the declaration of the Stack class.

#ifndef STACK_H
#define STACK_H

#include <stack>
#include <string>
#include <set>

using Symbol = char;

class Stack {
 public:
  Stack(const std::set<Symbol>& stack_alphabet, Symbol start_stack_symbol);
  Stack(const std::set<Symbol>& stack_alphabet, const std::stack<Symbol>& existing_stack) : stack_alphabet_{stack_alphabet}, stack_{existing_stack} {}
  ~Stack() = default;

  Stack GetStackCopy() const;
  std::string GetStackContentAsString() const;
  
  void Push(const Symbol& symbol);
  Symbol Pop();
  Symbol Top() const;
  bool IsEmpty() const;
 private:
  std::stack<Symbol> stack_;
  // I use a reference because a lot of Stack objects will be created during the execution of the program (it is recursive),
  // and I don't want to copy the stack alphabet every time, all will be references to the original set of the automaton.
  const std::set<Symbol>& stack_alphabet_;
};

#endif 