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
	rm -rf build/* $(TARGET)

cleano:
	rm -rf build/*

.PHONY: all clean cleano