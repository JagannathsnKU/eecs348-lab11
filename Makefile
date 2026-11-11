CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: lab11

lab11: lab11.cpp
	$(CXX) $(CXXFLAGS) lab11.cpp -o lab11

clean:
	rm -f lab11
