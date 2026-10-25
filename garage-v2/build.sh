#!/bin/bash
set -e
g++ -std=c++17 -Wall -Wextra -Werror -g -fsanitize=address,undefined main.cpp Vehicle.cpp Car.cpp Truck.cpp Motorcycle.cpp Garage.cpp -o m
./m "$@"
