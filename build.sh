#!/bin/sh
pkill uni-platform-game-bin
gcc -g -pthread --std=c++17 -lstdc++ -o uni-platform-game-bin main.cpp data/game_vector.cpp utils/memory_utils.cpp utils/math_utils.cpp
