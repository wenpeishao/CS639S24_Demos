#!/bin/bash

# Compile the project
make

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Run the program
./cg_solver

# Optionally, you can add commands to clean up after running
# make clean
