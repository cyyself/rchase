CXX = g++
CXXFLAGS = -O3 -std=c++17

rchase: rchase.cpp
	$(CXX) $(CXXFLAGS) -o rchase rchase.cpp