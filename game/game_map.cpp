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
	wall_padding(_wall_padding)
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
			map_text[i] = new char[game_width];
			utils::memory_utils::memory_set(map_text[i], ' ', game_width);
		}
		map_width = game_width;
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
			map_text[i] = new char[map_width];
			utils::memory_utils::memory_copy(map_text[i], old_map[i], map_width - game_width);
			delete[] old_map[i];
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
	}

	for(int i = new_section_index; i < map_width; i++)
	{
		for(int y = 0; y < wall_padding; y++)
		{
			char render_char = i % 4 ? '=' : '-';
			map_text[y][i] = map_text[map_height - 1 - y][i] = render_char;
		}
	}
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
		for(int k = 0; k < utils::runtime_utils::strlen(map_text[i]); k++)
			get_game_io()->draw(k, i, k % 4 ? console::color::magenta : console::color::cyan, false, map_text[i][k]);
}

void game::game_map::tick()
{

}

bool game::game_map::on_keyboard(int character)
{
	return false;
}
