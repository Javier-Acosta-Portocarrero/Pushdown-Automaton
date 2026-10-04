// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main_functions.h: declaration file.
// Contains the declaration of the main program auxiliary functions.

#ifndef PROGRAM_FUNCTIONS_H
#define PROGRAM_FUNCTIONS_H

#include "pushdown_automaton.h"

#include <string>

void ReadProgramArguments(int argc, char* argv[], std::string& config_file, std::string& input_file, bool& trace_active, bool& parameter_error);
void ExecuteInputFile(PushdownAutomaton& automaton, const std::string& input_file);
void ExecuteKeyboardInput(PushdownAutomaton& automaton);

#endif