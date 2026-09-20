CXX = g++
CXXFLAGS = -std=c++23
TARGET = build/pushdown_automaton

SOURCES = src\
          src

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