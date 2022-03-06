CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall
EXE=BHPCPatcher

all: $(EXE)

$(EXE): BHPCPatcher.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -static

clean:
	rm -f $(EXE)
