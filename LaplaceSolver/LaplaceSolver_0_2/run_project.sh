#!/bin/bash

# Compile the project
make clean
make

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Running single-threaded version..."
./conjugate_gradients_single
echo "Single-threaded version finished."

echo "Running multi-threaded version..."
./conjugate_gradients_multi
echo "Multi-threaded version finished."
