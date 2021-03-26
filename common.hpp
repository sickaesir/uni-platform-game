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
