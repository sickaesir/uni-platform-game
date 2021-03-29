#pragma once

// std libraries
#include <stdarg.h> // used for variadic args manipulation
#include <ncurses.h>

// custom types
typedef unsigned char byte;

// game default settings
namespace settings
{
	constexpr const int game_height = 60; // game height (console excluded)
	constexpr const int game_width = 100; // game width (applies to map)
	constexpr const int map_wall_padding = 3; // map wall sizes
	constexpr const bool console_mode = false; // console rendering
	constexpr const int console_lines = 5; // console line count
	constexpr const int io_inactive_ticks = 100; // number of ticks before signaling inactivity
	constexpr const int character_jump_velocity = 10; // the unit size of a single jump
	constexpr const int gravity_ticks = 50; // ticks count before processing a gravity-related tick
	constexpr const int map_offsetting_min = 30; // character position after which the map offset starts to decrease
	constexpr const int map_offsetting_max = 30; // character position after which the map offset starts to increase
	constexpr const int map_offset_threshold = 100; // limit after which the game map gets extended
};

// console settings
namespace console
{
	enum class color : short int
	{
		black = 1,
		blue,
		green,
		cyan,
		red,
		magenta,
		yellow,
		white
	};
};
