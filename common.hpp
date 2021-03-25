#pragma once

// std libraries
#include <stdio.h> // console i/o
#include <stdarg.h> // used for variadic args manipulation

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

// console codes
namespace console_code
{
	constexpr const char* reset_cursor_position = "\033[0;0H";
	constexpr const char* clear_screen = "\033[2J";
	constexpr const char* hide_cursor = "\033[?25l";
};
