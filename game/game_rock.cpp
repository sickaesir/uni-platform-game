#include "game_rock.hpp"
#include "../utils/runtime_utils.hpp"
#include "../utils/memory_utils.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"

game::game_rock::game_rock(game_component* parent, int rock_index) :
	game_component(parent, "game_rock")
{
	parse_rock_by_index(rock_index);
}

game::game_rock::~game_rock()
{
	for(int i = 0; i < rock_height; i++)
		delete[] rock_text[i];
	delete[] rock_text;
}

void game::game_rock::parse_rock_by_index(int rock_index)
{
	const char* rock_data = sprites::rocks[rock_index];
	data::data_vector<char*> rock_lines;
	utils::runtime_utils::str_split((char*)rock_data, '\n', rock_lines);

	rock_height = rock_lines.get_size();
	rock_text = new char*[rock_height];
	rock_width = 0;
	for(int i = 0; i < rock_height; i++)
	{
		int line_len = utils::runtime_utils::strlen(rock_lines[i]);
		if(line_len > rock_width)
			rock_width = line_len;
		rock_text[i] = new char[line_len + 1];
		utils::memory_utils::memory_set_zero<char>(rock_text[i], line_len + 1);
		utils::memory_utils::memory_copy<char>(rock_text[i], rock_lines[i], line_len);
	}

}

void game::game_rock::render()
{
	for(int y = 0; y < rock_height; y++)
	{
		for(int x = 0; x < rock_width; x++)
		{
			int render_x = pos_x() + x - get_game_map()->get_map_offset();
			if(render_x < 0
				|| render_x > get_game_settings()->get_game_width())
				continue;

			if(rock_text[y][x] == ' ')
				continue;

			get_game_io()->draw(render_x, pos_y() + y, console::color::magenta, false, rock_text[y][x]);
		}
	}
}

int game::game_rock::get_rock_height()
{
	return rock_height;
}

int game::game_rock::get_rock_width()
{
	return rock_width;
}
