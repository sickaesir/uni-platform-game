#include "../common.hpp"
#include "game_map.hpp"
#include "../utils/memory_utils.hpp"

game::game_map::game_map() :
	map_width(0),
	map_height(0)
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
		map_text = new char*[settings::game_height];
		map_height = settings::game_height;
		for(int i = 0; i < map_height; i++)
		{
			map_text[i] = new char[settings::game_width];
			utils::memory_utils::memory_set(map_text[i], ' ', settings::game_width);
		}
		map_width = settings::game_width;
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

		map_width += settings::game_width;

		for(int i = 0; i < map_height; i++)
		{
			map_text[i] = new char[map_width];
			utils::memory_utils::memory_copy(map_text[i], old_map[i], map_width - settings::game_width);
			delete[] old_map[i];
		}

		delete[] old_map;

	}

	int new_section_index = map_width - settings::game_width;

	if(map_width == settings::game_width)
		for(int i = 3; i < map_height - 3; i++)
			for(int x = 0; x < 3; x++)
				map_text[i][x] = '|';

	for(int i = new_section_index; i < map_width; i++)
	{
		for(int y = 0; y < 3; y++)
		{
			map_text[y][i] = '_';
			map_text[map_height - 1 - y][i] = '-';
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
		std::cout << map_text[i] << std::endl;
}

void game::game_map::tick()
{

}
