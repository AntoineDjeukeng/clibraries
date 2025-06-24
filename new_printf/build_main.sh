#!/bin/bash
make valgrind
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./main.out
