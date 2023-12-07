CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRC = $(wildcard *.cpp)
EXECUTABLES = $(patsubst %.cpp,%,$(SRC))

.PHONY: all clean

all: $(EXECUTABLES)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)
	rm -rf $(wildcard *.dSYM)

