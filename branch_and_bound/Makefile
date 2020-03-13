CXX=g++
CXXFLAGS=-g -std=c++11 -Wall

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

.PHONY: all
all: main

.PHONY: clean
clean:
	rm -f $(obj)

main: $(obj)
	$(CXX) -o $@ $^