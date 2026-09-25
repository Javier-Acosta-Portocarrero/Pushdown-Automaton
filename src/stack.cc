// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 25/09/2026
// File stack.cc: implementation file.
// Contains the implementation of the Stack class.

#include "../include/stack.h"

#include <stdexcept>

/**
 * @brief Constructor for the Stack class.
 * @param stack_alphabet Set of symbols that form the stack alphabet.
 * @param start_stack_symbol Initial symbol to be pushed onto the stack.
 */
Stack::Stack(const std::set<Symbol>& stack_alphabet, Symbol start_stack_symbol) : stack_alphabet_(stack_alphabet) {
  if (!stack_alphabet_.contains(start_stack_symbol)) {
    throw std::runtime_error("The start stack symbol \"" + std::string(1, start_stack_symbol) + "\" is not in the stack alphabet.");
  }
  stack_.push(start_stack_symbol);
}

/**
 * @brief Returns a copy of the current stack.
 * @return A copy of the current stack.
 */
Stack Stack::GetStackCopy() const {
  Stack stack_copy{stack_alphabet_, stack_};
  return stack_copy;
}

/**
 * @brief Returns the content of the stack as a string, used for traces.
 * @return A string representing the content of the stack.
 */
std::string Stack::GetStackContentAsString() const {
  if (stack_.empty()) {
    return ".";  // Recordatory, I'm using '.' as an equivalent to epsilon.
  }
  std::stack<Symbol> tmp_stack = stack_;
  std::string stack_content = "";
  while (!tmp_stack.empty()) {
    stack_content += tmp_stack.top();
    tmp_stack.pop();
  }
  return stack_content;
}

/**
 * @brief Pushes a symbol onto the stack.
 * @param symbol Symbol to be pushed onto the stack.
 */
void Stack::Push(const Symbol& symbol) {
  if (!stack_alphabet_.contains(symbol)) {
    throw std::runtime_error("The symbol \"" + std::string(1, symbol) + "\" to be pushed in the stack is not in the stack alphabet.");
  }
    stack_.push(symbol);
}

/**
 * @brief Pops the top symbol from the stack.
 * @return The symbol that was popped from the stack.
 */
Symbol Stack::Pop() {
  if (stack_.empty()) {
    throw std::runtime_error("Cant pop from an empty stack.");
  }
  Symbol top_symbol = stack_.top();
  stack_.pop();
  return top_symbol;
}

/**
 * @brief Returns the top symbol of the stack without removing it.
 * @return The top symbol of the stack.
 */
Symbol Stack::Top() const {
  if (stack_.empty()) {
    throw std::runtime_error("Cant get the top symbol of an empty stack.");
  }
  return stack_.top();
}

/**
 * @brief Checks if the stack is empty.
 * @return true if the stack is empty, false otherwise.
 */
bool Stack::IsEmpty() const {
  return stack_.empty();
}