CXX = g++
CXXFLAGS = -std=c++11 -O2 -fopenmp

# Define the source files and the target executable
SRCS = main.cpp ConjugateGradients.cpp Utilities.cpp Laplacian.cpp PointwiseOps.cpp Reductions.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = cg_solver

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
