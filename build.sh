#!/bin/sh
pkill uni-platform-game-bin
gcc -g -pthread --std=c++17 -lstdc++ -o uni-platform-game-bin main.cpp game/game.cpp
