#pragma once

// std libraries
#include <stdarg.h> // used for variadic args manipulation
#include <ncurses.h>

// custom types
typedef unsigned char byte;

// game default settings
namespace settings
{
	constexpr const int game_height = 60;
	constexpr const int game_width = 100;
	constexpr const int map_wall_padding = 3;
	constexpr const bool console_mode = false;
	constexpr const int console_lines = 5;
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
