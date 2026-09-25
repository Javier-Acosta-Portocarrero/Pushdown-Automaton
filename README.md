# Pushdown-Automaton

This is an academic project consisting of the implementation of a empty stack focused pushdown automaton from scratch in C++, with an object-oriented design and following some design patterns, such as the Strategy pattern.

## Author

Javier Acosta Portocarrero - alu0101660769@ull.edu.es - javier.acosta.porto@gmail (personal)

## Structure

I structured the program in the next main classes:

- **InputString**: consists of a string and an index to simulate the movement through the input string. I tried to use references as much as possible because of the recursive nature of my automaton, trying to be as efficient with the memory as possible. 
- **Stack**: wraps a `std::stack` and controls that every symbol introduced into it belongs to the stack alphabet. I store the stack alphabet as a reference because, due to the recursive nature of the automaton (as said before), a lot of `Stack` objects are created during the execution and I didn't want to copy the complete alphabet every time. It also provides methods to copy the current stack, get its content as a string for the trace and other classic methods (push, pop, top).
- **InstantaneousDescription**: consists of the information needed by the transition function to know which transitions can be made in the current moment. It contains the current state, the symbol at the top of the stack and the current symbol of the input string. 
- **TransitionEffects**: represents the effects of applying a transition. It contains the destination state, the symbols that have to be introduced into the stack and an identifier for each transition, needed to always follow the same criterion on the order of the transition to execute (based on the order of the input file). It also stores if the transition consumes a symbol from the input string or not, which is needed for epsilon transitions. 
- **TransitionFunction**: contains and manages all the transitions of the automaton. I used maps and multimaps to organize the transitions depending on the current state, the symbol at the top of the stack and the current input symbol. Since the automaton is non-deterministic, there can be more than one possible transition for the same situation, thats the reason I used multimaps with the entry symbols as keys. 
- **PushdownAutomaton**: represents the automaton itself. It contains the states, input alphabet, stack alphabet, initial state, initial stack symbol and the transition function. To check if a word is accepted, the automaton recursively checks all the possible transitions with a **DFS strategy**. As this implementation is focused on empty stack acceptance, a word is accepted when the complete input string has been consumed and the stack is empty. 
- **PushdownAutomatonLoaderStrategy**: abstract class that defines the interface that an automaton loader strategy has to follow. I used the Strategy pattern here so different ways of loading an automaton could be added without changing the rest of the program. 
- **PushdownAutomatonLoaderPlainTextStrategy**: implementation of the loader strategy for plain text files. It reads all the information of the automaton from the configuration file and checks that the format and content are correct. For example, it checks that used states belong to the set of states and that used symbols belong to their respective alphabets. The `.` character is used as the representation of epsilon. 
- **PushdownAutomatonLoader**: manages the strategy used to load the automaton. It receives a `PushdownAutomatonLoaderStrategy` and uses it to create the `PushdownAutomaton`. This way the main program does not need to know how the automaton is actually loaded. 

The `main` program is in charge of reading the command line arguments, loading the automaton, enabling or disabling the trace and reading the input strings. The strings can be introduced manually through the terminal or read from a file using the `-in` option.

## How to execute the program

First, you need to have installed `g++` with support for C++23 and `make`.

To compile the complete project, execute from the root directory:

```bash
make
```

The executable will be generated inside the `build` directory:

```bash
build/pushdown_automaton
```

To remove all the compiled files:

```bash
make clean
```

The program has two obligatory parameters, `-config` and `-trace`, and an optional one, `-in`:

```bash
./build/pushdown_automaton -config <file> -trace <y|n> [-in <file>]
```
Each parameter has the following meaning:

- `-config <file>` specifies the plain text file containing the pushdown automaton configuration.
- `-trace <y|n>` specifies if the execution trace should be shown or not.
- `-in <file>` is optional and specifies a file containing the input strings to check, if not given, the strings can be introduced manually in the terminal.

When introducing the strings manually, type `exit` to stop the execution.