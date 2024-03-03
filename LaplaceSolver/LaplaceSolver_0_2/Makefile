CXX=g++
CXXFLAGS=-std=c++11 -O3
SOURCES=main.cpp ConjugateGradients.cpp Utilities.cpp PointwiseOps.cpp Reductions.cpp Laplacian.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=conjugate_gradients
EXECUTABLE_SINGLE=$(EXECUTABLE)_single
EXECUTABLE_MULTI=$(EXECUTABLE)_multi

# Default target
all: $(EXECUTABLE_SINGLE) $(EXECUTABLE_MULTI)

# Single-threaded version
$(EXECUTABLE_SINGLE): CXXFLAGS += -DNO_OMP
$(EXECUTABLE_SINGLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Multi-threaded version
$(EXECUTABLE_MULTI): CXXFLAGS += -fopenmp
$(EXECUTABLE_MULTI): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean objects and executables
clean:
	rm -f $(EXECUTABLE_SINGLE) $(EXECUTABLE_MULTI)

.PHONY: all clean
