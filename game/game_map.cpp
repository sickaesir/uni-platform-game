#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "../utils/memory_utils.hpp"
#include "game_io.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"
#include "game_rock.hpp"

game::game_map::game_map(game_component* parent, int _game_height, int _game_width, int _wall_padding) : 
	game_component(parent, "game_map"),
	map_width(0),
	map_height(0),
	game_width(_game_width),
	game_height(_game_height),
	wall_padding(_wall_padding),
	map_offset(0),
	rocks_to_generate(0)
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
			utils::memory_utils::memory_set<char>(map_text[i], ' ', game_width);
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
			utils::memory_utils::memory_copy<char>(old_map[i], map_text[i], map_width);
			delete[] map_text[i];
		}

		map_width += game_width;

		for(int i = 0; i < map_height; i++)
		{
			map_text[i] = new char[map_width + 1];
			utils::memory_utils::memory_copy<char>(map_text[i], old_map[i], map_width - game_width);
			utils::memory_utils::memory_set<char>(map_text[i] + map_width - game_width, ' ', game_width);
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

	rocks_to_generate += get_game_settings()->get_rocks_gen_count();
}

void game::game_map::generate_rock(unsigned int x_offset)
{
	if(!rocks_to_generate)
		return;

	int rock_index = get_game_instance()->urandom_number(0, sprites::rocks_count - 1);
	game_rock* rock = new game_rock(this, rock_index);

	int x = get_game_instance()->urandom_number(x_offset + wall_padding, x_offset + map_width - rock->get_rock_width());
	int y = get_game_instance()->urandom_number(wall_padding, map_height - wall_padding - rock->get_rock_height());
	rock->pos_x(x);
	rock->pos_y(y);

	int padding = get_game_settings()->get_rock_gen_collision_padding();
	for(int rx = -padding; rx < rock->get_rock_width() + padding; rx++)
	{
		for(int ry = -padding; ry < rock->get_rock_height() + padding; ry++)
		{
			if(get_game_instance()->check_collision(rock, x + rx - map_offset, y + ry))
			{
				delete rock;
				return;
			}
		}

	}

	add_component(rock);
	rocks_to_generate--;
}

game::game_component* game::game_map::check_collision(game_component* requester, int x, int y)
{
	if(x < wall_padding || y < wall_padding)
		return this;

	if(y > map_height - wall_padding - 1)
		return this;

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

	game_component::render();
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
	if(map_width - map_offset < get_game_settings()->get_map_offset_threshold())
	{
		extend_map();
	}
	generate_rock(map_width - game_width);
}

void game::game_map::decrement_map_offset()
{
	map_offset--;
}

int game::game_map::get_map_offset()
{
	return map_offset;
}
