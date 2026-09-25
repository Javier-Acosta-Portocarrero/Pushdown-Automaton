CXX = g++
CXXFLAGS = -std=c++23
TARGET = build/pushdown_automaton

SOURCES = src/pushdown_automaton_load/pushdown_automaton_loader_plain_text_strategy.cc src/pushdown_automaton_load/pushdown_automaton_loader.cc\
          src/input_string.cc src/main.cc src/pushdown_automaton.cc src/transition_effects.cc src/transition_function.cc src/stack.cc

OBJECTS = $(SOURCES:%.cc=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*

cleano:
	rm -rf build/src

.PHONY: all clean cleano