CXX = g++
CXXFLAGS = -std=c++17 -Wall

all:
	$(CXX) $(CXXFLAGS) Vector.cpp -o vector_test
