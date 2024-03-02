# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -O3 -fopenmp
LDFLAGS = -fopenmp
LIBS = 

# Makefile settings - the file extension for C++ source files
EXT = cpp

# List of all .cpp files.
CPP_FILES := $(wildcard *.$(EXT))

# Object files have same name as .cpp files, but with .o extension.
OBJ_FILES := $(CPP_FILES:.$(EXT)=.o)

# The executable program to build:
TARGET = ConjugateGradients

# Build the main program.
$(TARGET): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Build .o object files from .cpp source files.
%.o: %.$(EXT)
	$(CXX) $(CXXFLAGS) -c $<

# Clean up build.
clean:
	rm -f $(TARGET) $(OBJ_FILES)

# A target to run the program.
run: $(TARGET)
	./$(TARGET)

# A phony target to force make to run, even if it thinks it doesn't need to.
.PHONY: clean run
