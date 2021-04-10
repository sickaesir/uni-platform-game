#!/bin/sh
pkill uni-platform-game-bin
g++ -g -pthread --std=c++17 -lstdc++ -lncursesw -o uni-platform-game-bin \
	main.cpp		\
	data/data_point.cpp	\
	game/game_settings.cpp	\
	game/game_component.cpp \
	game/game.cpp		\
	game/game_map.cpp	\
	game/game_io.cpp	\
	game/game_character.cpp \
	game/game_rock.cpp	\
	game/game_laser.cpp	\
	game/game_powerup.cpp	\
	game/game_enemy.cpp	\
	game/game_trooper.cpp
