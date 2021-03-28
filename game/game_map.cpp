#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "../utils/memory_utils.hpp"
#include "game_io.hpp"
#include "../utils/runtime_utils.hpp"

game::game_map::game_map(game_component* parent, int _game_height, int _game_width, int _wall_padding) : 
	game_component(parent, "game_map"),
	map_width(0),
	map_height(0),
	game_width(_game_width),
	game_height(_game_height),
	wall_padding(_wall_padding),
	map_offset(0)
{
	extend_map();
}

game::game_map::~game_map()
{
	for(int i = 0; i < map_height; i++)
	{
		delete map_text[i];
		map_text[i] = nullptr;
	}
	delete[] map_text;
}

void game::game_map::extend_map()
{
	if(!map_height)
	{
		map_text = new char*[game_height];
		map_height = game_height;
		for(int i = 0; i < map_height; i++)
		{
			map_text[i] = new char[game_width + 1];
			utils::memory_utils::memory_set(map_text[i], ' ', game_width);
			map_text[i][game_width] = 0x00;
		}
		map_width = game_width;
		log("initialized map data");
	}
	else
	{
		char** old_map = new char*[map_height];
		for(int i = 0; i < map_height; i++)
		{
			old_map[i] = new char[map_width];
			utils::memory_utils::memory_copy(old_map[i], map_text[i], map_width);
			delete[] map_text[i];
		}

		map_width += game_width;

		for(int i = 0; i < map_height; i++)
		{
			map_text[i] = new char[map_width + 1];
			utils::memory_utils::memory_copy(map_text[i], old_map[i], map_width - game_width);
			utils::memory_utils::memory_set(map_text[i] + map_width - game_width, ' ', game_width);
			delete[] old_map[i];
			map_text[i][map_width] = 0x00;
		}

		delete[] old_map;

	}

	int new_section_index = map_width - game_width;

	if(map_width == game_width)
	{
		for(int i = wall_padding; i < map_height - wall_padding; i++)
		{
			for(int x = 0; x < wall_padding; x++)
			{
				map_text[i][x] = '|';
			}
		}

		log("initialized map left-most wall");
	}

	for(int i = new_section_index; i < map_width; i++)
	{
		for(int y = 0; y < wall_padding; y++)
		{
			char render_char = i % 4 ? '=' : '-';
			map_text[y][i] = map_text[map_height - 1 - y][i] = render_char;
		}
	}

	log("map expanded, x axis is now %d unit long", map_width);
}

bool game::game_map::check_collision(game_component* requester, int x, int y)
{
	if(x < wall_padding || y < wall_padding)
		return true;

	if(y > map_height - wall_padding - 1)
		return true;

	return game_component::check_collision(requester, x, y);
}

int game::game_map::height()
{
	return map_height;
}

int game::game_map::width()
{
	return map_width;
}

void game::game_map::render()
{
	for(int i = 0; i < map_height; i++)
		for(int c = 0, k = map_offset; k < game_width + map_offset + 1; k++, c++)
			get_game_io()->draw(c, i, k % 4 ? console::color::magenta : console::color::cyan, false, map_text[i][k]);
}

void game::game_map::tick()
{

}

bool game::game_map::on_keyboard(int character)
{
	return false;
}

void game::game_map::increment_map_offset()
{
	map_offset++;
	if(map_width - map_offset < 100)
		extend_map();
}

void game::game_map::decrement_map_offset()
{
	map_offset--;
}

int game::game_map::get_map_offset()
{
	return map_offset;
}
