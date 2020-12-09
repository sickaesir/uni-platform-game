#pragma once

// std libraries
#include <iostream>

// custom types
typedef unsigned char byte;

// game settings
namespace settings
{
  constexpr const int game_height = 30;
  constexpr const int game_width = 90;
};

// console codes
namespace console_code
{
  constexpr const char* reset_cursor_position = "\033[0;0H";
  constexpr const char* clear_screen = "\033[2J";
  constexpr const char* hide_cursor = "\033[?25l";
}
