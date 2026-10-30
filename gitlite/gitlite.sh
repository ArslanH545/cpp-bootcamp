#!/bin/bash
set -e
g++ -std=c++17 -Wall -Wextra -Werror -g -fsanitize=address,undefined main.cpp -o m
./m "$@"
