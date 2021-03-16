#!/bin/sh
pkill uni-platform-game-bin
gcc -g -pthread --std=c++17 -lstdc++ -lncursesw -o uni-platform-game-bin \
	main.cpp \
	game/game.cpp \
	game/game_map.cpp \
	game/game_input.cpp
