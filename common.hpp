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
	constexpr const int gravity_ticks = 70; // ticks count before processing a gravity-related tick
	constexpr const int map_offsetting_min = 30; // character position after which the map offset starts to decrease
	constexpr const int map_offsetting_max = 30; // character position after which the map offset starts to increase
	constexpr const int map_offset_threshold = 100; // limit after which the game map gets extended
	constexpr const int rocks_gen_count = 10; // amount of rocks to generate at every map chunk
	constexpr const int rock_gen_collision_padding = 3; // distance between other components for a collision free rock
	constexpr const int max_character_life = 100; // max life points for the main game character
	constexpr const int character_reattack_ticks = 300; // ticks between every character shot
	constexpr const int powerup_heal_amount = 10; // amount of life points healed by heal powerup
	constexpr const int powerup_max_gen_amount = 1; // maximum amount of powerup to generate at each map extension
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

namespace sprites
{
	constexpr unsigned int rocks_count = 5; // amount of rock sprites defined in sprites::rocks array
	constexpr const char* rocks[] = {
		"/=======-=======\\\n" \
		"|               |\n" \
		"\\___        ___/\n" \
		"     \\     /    \n" \
		"      -----      ",

		"-===-===-===-===-\n" \
		"=================",

		"(^^^^^^^^^)\n" \
		"(vvvvvvvvv)",

		"|=====================|\n" \
		"   |===============|   \n" \
		"      |=========|      ",

		"(================)\n" \
		" (-:-:-:-:-:-:-:) \n" \
		"   (:-:-:-:-:-)   \n" \
		"        vvv        "
	};

	constexpr unsigned int lasers_count = 5;
	constexpr const char* lasers[] = {
		"--->",
		"<---",
		"======>",
		"<======",
		"^-v-^-v-^-->",
		"<--^-v-^-v-^",
		">>>>>>>>>>>>>>>>",
		"<<<<<<<<<<<<<<<<",
		"-:-:-:-:-:-:-:-:-:-:->",
		"<-:-:-:-:-:-:-:-:-:-:-"
	};

	constexpr const char* map_ground_pattern = "===-";
};
