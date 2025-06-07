#!/bin/bash

# Name of the final executable
EXEC=main_test

# Compile with debug flags and link the library
gcc -Wall -Wextra -Werror -O0 -g main.c ft_printf.a -o $EXEC

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "✅ Compilation successful. Running with Valgrind..."
    valgrind --leak-check=full --show-leak-kinds=all ./$EXEC
else
    echo "❌ Compilation failed."
fi
