// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton_loader_plain_text_strategy.cc: implementation file.
// Contains the implementation of the PushdownAutomatonLoaderPlainTextStrategy class.

#include "../../include/pushdown_automaton_load/pushdown_automaton_loader_plain_text_strategy.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Loads a pushdown automaton from a plain text configuration file.
 * @param file_path Path to the configuration file.
 * @return Pushdown automaton loaded from the file.
 */
PushdownAutomaton PushdownAutomatonLoaderPlainTextStrategy::LoadPushdownAutomaton(const std::string& file_path) const {
  std::ifstream input_file{file_path};
  if (!input_file.is_open()) {
    throw std::runtime_error("Could not open file '" + file_path + "'.");
  }
  unsigned line_number = 0;

  const std::string states_line = GetNextContentLine(input_file, line_number, "the automaton states");
  const std::set<std::string> automaton_states = ReadStates(states_line, line_number);

  const std::string input_alphabet_line = GetNextContentLine(input_file, line_number, "the input alphabet");
  const std::set<Symbol> input_alphabet = ReadAlphabet(input_alphabet_line, line_number, "input alphabet");

  const std::string stack_alphabet_line = GetNextContentLine(input_file, line_number, "the stack alphabet");
  const std::set<Symbol> stack_alphabet = ReadAlphabet(stack_alphabet_line, line_number, "stack alphabet");

  const std::string start_state_line = GetNextContentLine(input_file, line_number, "the initial state");
  const std::string start_state = ReadSingleElement(start_state_line, line_number, "initial state");

  if (!automaton_states.contains(start_state)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": state '" + start_state + "' is not an automaton state.");
  }

  const std::string start_stack_symbol_line = GetNextContentLine(input_file, line_number, "the initial stack symbol");
  const std::string start_stack_symbol_string = ReadSingleElement(start_stack_symbol_line, line_number, "initial stack symbol");
  if (start_stack_symbol_string.size() != 1) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": the initial stack symbol must be one character.");
  }
  const Symbol start_stack_symbol = start_stack_symbol_string[0];
  if (start_stack_symbol == '.') {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": the initial stack symbol cannot be epsilon.");
  }
  if (!stack_alphabet.contains(start_stack_symbol)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": initial stack symbol '" + start_stack_symbol_string + "' is not in the stack alphabet.");
  }

  TransitionFunction transition_function;
  unsigned transition_identifier = 1;
  std::string line;
  while (std::getline(input_file, line)) {
    ++line_number;
    line = RemoveCommentsAndWhitespace(line);
    if (line.empty()) {
      continue;
    }
    ReadTransition(line, line_number, transition_identifier, automaton_states, input_alphabet, stack_alphabet, transition_function);
    ++transition_identifier;
  }

  return PushdownAutomaton{transition_function, input_alphabet, stack_alphabet, start_stack_symbol, automaton_states, start_state};
}

/**
 * @brief Reads the next non-empty line that contains useful information.
 * @param input_file Input configuration file.
 * @param line_number Current line number.
 * @param expected_content Content expected in the file.
 * @return Next valid content line.
 */
std::string PushdownAutomatonLoaderPlainTextStrategy::GetNextContentLine(std::ifstream& input_file, unsigned& line_number, const std::string& expected_content) const {
  std::string line;
  while (std::getline(input_file, line)) {
    ++line_number;
    line = RemoveCommentsAndWhitespace(line);

    if (!line.empty()) {
      return line;
    }
  }

  throw std::runtime_error("Unexpected end of file, expected " + expected_content + ".");
}

/**
 * @brief Removes comments and unnecessary spaces from a line.
 * @param line Line to process.
 * @return Processed line.
 */
std::string PushdownAutomatonLoaderPlainTextStrategy::RemoveCommentsAndWhitespace(const std::string& line) const {
  std::string processed_line = line;
  const std::size_t comment_position = processed_line.find('#');
  if (comment_position != std::string::npos) {
    processed_line.erase(comment_position);
  }
  const std::size_t first_character = processed_line.find_first_not_of(" \t\r\n");
  if (first_character == std::string::npos) {
    return "";
  }
  const std::size_t last_character = processed_line.find_last_not_of(" \t\r\n");

  return processed_line.substr(first_character, last_character - first_character + 1);
}

/**
 * @brief Reads and checks the automaton states.
 * @param line Line containing the states.
 * @param line_number Line number in the file.
 * @return Set of automaton states.
 */
std::set<std::string> PushdownAutomatonLoaderPlainTextStrategy::ReadStates(const std::string& line, unsigned line_number) const {
  std::istringstream line_stream{line};
  std::set<std::string> states;
  std::string state;
  while (line_stream >> state) {
    if (states.contains(state)) {
      throw std::runtime_error("Line " + std::to_string(line_number) + ": state '" + state + "' is repeated.");
    }
    states.insert(state);
  }
  if (states.empty()) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": there must be at least one state.");
  }

  return states;
}

/**
 * @brief Reads and checks an automaton alphabet.
 * @param line Line containing the alphabet.
 * @param line_number Line number in the file.
 * @param alphabet_name Name of the alphabet.
 * @return Set of symbols of the alphabet.
 */
std::set<Symbol> PushdownAutomatonLoaderPlainTextStrategy::ReadAlphabet(const std::string& line, unsigned line_number, const std::string& alphabet_name) const {
  std::istringstream line_stream{line};
  std::set<Symbol> alphabet;
  std::string symbol_string;

  while (line_stream >> symbol_string) {
    if (symbol_string.size() != 1) {
      throw std::runtime_error("Line " + std::to_string(line_number) + ": symbol '" + symbol_string + "' in the " + alphabet_name + " must be one character.");
    }
    const Symbol symbol = symbol_string[0];
    if (symbol == '.') {
      throw std::runtime_error("Line " + std::to_string(line_number) + ": '.' is epsilon, it cannot be part of the " + alphabet_name + ".");
    }
    if (alphabet.contains(symbol)) {
      throw std::runtime_error("Line " + std::to_string(line_number) + ": symbol '" + symbol_string + "' is repeated in the " + alphabet_name + ".");
    }

    alphabet.insert(symbol);
  }
  if (alphabet.empty()) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": the " + alphabet_name + " cannot be empty.");
  }

  return alphabet;
}

/**
 * @brief Reads a line that must contain only one element.
 * @param line Line containing the element.
 * @param line_number Line number in the file.
 * @param element_name Name of the expected element.
 * @return Element read from the line.
 */
std::string PushdownAutomatonLoaderPlainTextStrategy::ReadSingleElement(const std::string& line, unsigned line_number, const std::string& element_name) const {
  std::istringstream line_stream{line};
  std::string element;
  std::string extra_element;

  if (!(line_stream >> element)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": expected " + element_name + ".");
  }
  if (line_stream >> extra_element) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": there should only be one " + element_name + ".");
  }

  return element;
}

/**
 * @brief Reads, checks and adds one transition to the transition function.
 * @param line Line containing the transition.
 * @param line_number Line number in the file.
 * @param transition_identifier Identifier of the transition.
 * @param automaton_states Set of automaton states.
 * @param input_alphabet Input alphabet.
 * @param stack_alphabet Stack alphabet.
 * @param transition_function Transition function where the transition will be added.
 */
void PushdownAutomatonLoaderPlainTextStrategy::ReadTransition(const std::string& line, unsigned line_number, unsigned transition_identifier, 
    const std::set<std::string>& automaton_states, const std::set<Symbol>& input_alphabet, const std::set<Symbol>& 
    stack_alphabet, TransitionFunction& transition_function) const {

  std::istringstream line_stream{line};
  std::string source_state;
  std::string input_symbol_string;
  std::string stack_top_string;
  std::string destination_state;
  std::string stack_replacement;
  std::string extra_element;
  if (!(line_stream >> source_state >> input_symbol_string >> stack_top_string >> destination_state >> stack_replacement)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": bad transition format, expected 5 elements.");
  }
  if (line_stream >> extra_element) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": bad transition format, expected only 5 elements.");
  }

  if (!automaton_states.contains(source_state)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": source state '" + source_state + "' is not an automaton state.");
  }
  if (!automaton_states.contains(destination_state)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": destination state '" + destination_state + "' is not an automaton state.");
  }
  if (input_symbol_string.size() != 1) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": input symbol '" + input_symbol_string + "' must be one character.");
  }

  const Symbol input_symbol = input_symbol_string[0];
  if (input_symbol != '.' && !input_alphabet.contains(input_symbol)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": input symbol '" + input_symbol_string + "' is not in the input alphabet.");
  }
  if (stack_top_string.size() != 1) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": stack symbol '" + stack_top_string + "' must be one character.");
  }

  const Symbol stack_top = stack_top_string[0];
  if (stack_top == '.') {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": epsilon cannot be used as the stack top.");
  }
  if (!stack_alphabet.contains(stack_top)) {
    throw std::runtime_error("Line " + std::to_string(line_number) + ": stack symbol '" + stack_top_string + "' is not in the stack alphabet.");
  }

  if (stack_replacement == ".") {
    stack_replacement = "";
  } else {
    for (const Symbol symbol : stack_replacement) {
      if (!stack_alphabet.contains(symbol)) {
        throw std::runtime_error("Line " + std::to_string(line_number) + ": symbol '" + std::string(1, symbol) + "' in '" + stack_replacement + "' is not in the stack alphabet.");
      }
    }
  }

  InstantaneousDescription requirements{source_state, stack_top, input_symbol};
  TransitionEffects effects{stack_replacement, source_state, destination_state, transition_identifier};
  transition_function.AddNewTransition(requirements, effects);
}