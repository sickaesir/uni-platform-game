#include "game_trooper.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"


game::game_trooper::game_trooper(game_component* parent) : game_enemy(parent, game_component::component_type::trooper)
{

}

void game::game_trooper::tick()
{
	descend_tick();
	game_enemy::tick();
}

void game::game_trooper::descend_tick()
{
	for(int i = 0; i < get_enemy_width(); i++)
		if(check_game_collision(pos_x() - get_game_map()->get_map_offset() + i, pos_y() + 1))
			return;

	pos_y(pos_y() + 1);
}

void game::game_trooper::render()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();

	if(render_x < 0 || render_x > get_game_settings()->get_game_width())
		return;

	get_game_io()->draw(render_x, pos_y() - 2, console::color::cyan, true, '(');
	get_game_io()->draw(render_x + 1, pos_y() - 2, console::color::cyan, true, ')');
	get_game_io()->draw(render_x + 2, pos_y() - 2, console::color::green, true, '=');
	get_game_io()->draw(render_x + 3, pos_y() - 2, console::color::green, true, '=');
	get_game_io()->draw(render_x + 4, pos_y() - 2, console::color::cyan, true, '(');
	get_game_io()->draw(render_x + 5, pos_y() - 2, console::color::cyan, true, ')');
	get_game_io()->draw(render_x + 2, pos_y() - 1, console::color::red, true, '<');
	get_game_io()->draw(render_x + 3, pos_y() - 1, console::color::white, true, ']');
	get_game_io()->draw(render_x + 4, pos_y() - 1, console::color::red, true, '\\');
	get_game_io()->draw(render_x + 1, pos_y(), console::color::magenta, true, '*');
	get_game_io()->draw(render_x + 2, pos_y(), console::color::cyan, true, '~');
	get_game_io()->draw(render_x + 3, pos_y(), console::color::cyan, true, '\\');
	get_game_io()->draw(render_x + 4, pos_y(), console::color::cyan, true, '[');

	int offset_x = 0;

	if(pos_x() % 2)
	{
		++offset_x;
		get_game_io()->draw(render_x + 4 + offset_x, pos_y(), console::color::magenta, true, '=');
		++offset_x;
		get_game_io()->draw(render_x + 4 + offset_x, pos_y(), console::color::magenta, true, '-');
	}

	++offset_x;
	get_game_io()->draw(render_x + 4 + offset_x, pos_y(), console::color::cyan, true, '[');
	++offset_x;
	get_game_io()->draw(render_x + 4 + offset_x, pos_y(), console::color::cyan, true, '[');

	game_enemy::render();
}

unsigned int game::game_trooper::get_enemy_height()
{
	return 3;
}

unsigned int game::game_trooper::get_enemy_width()
{
	return 6;
}
