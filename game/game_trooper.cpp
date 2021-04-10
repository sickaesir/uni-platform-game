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
	move_tick();
	game_enemy::tick();
}

void game::game_trooper::descend_tick()
{
	for(int i = 0; i < get_enemy_width(); i++)
		if(check_game_collision(pos_x() - get_game_map()->get_map_offset() + i, pos_y() + 1))
			return;

	pos_y(pos_y() + 1);
}

void game::game_trooper::move_tick()
{
	if(get_tick_count() % 150) return;

	log("rel char x:%d y:%d", get_relative_character_x(), get_relative_character_y());

	pos_x(pos_x() + get_relative_character_x());
}

void game::game_trooper::render()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();


	auto draw_wrapper = [this](int x, int y, console::color color, char character) -> void {
		if(x < 0 || x > get_game_settings()->get_game_width())
			return;

		get_game_io()->draw(x, y, color, true, character);
	};

	draw_wrapper(render_x, pos_y() - 2, console::color::cyan, '(');
	draw_wrapper(render_x + 1, pos_y() - 2, console::color::cyan, ')');
	draw_wrapper(render_x + 2, pos_y() - 2, console::color::green, '=');
	draw_wrapper(render_x + 3, pos_y() - 2, console::color::green, '=');
	draw_wrapper(render_x + 4, pos_y() - 2, console::color::cyan, '(');
	draw_wrapper(render_x + 5, pos_y() - 2, console::color::cyan, ')');
	draw_wrapper(render_x + 2, pos_y() - 1, console::color::red, '<');
	draw_wrapper(render_x + 3, pos_y() - 1, console::color::white, ']');
	draw_wrapper(render_x + 4, pos_y() - 1, console::color::red, '\\');
	draw_wrapper(render_x + 1, pos_y(), console::color::magenta, '*');
	draw_wrapper(render_x + 2, pos_y(), console::color::cyan, '~');
	draw_wrapper(render_x + 3, pos_y(), console::color::cyan, '\\');
	draw_wrapper(render_x + 4, pos_y(), console::color::cyan, '[');

	int offset_x = 0;

	if(pos_x() % 2)
	{
		++offset_x;
		draw_wrapper(render_x + 4 + offset_x, pos_y(), console::color::magenta, '=');
		++offset_x;
		draw_wrapper(render_x + 4 + offset_x, pos_y(), console::color::magenta, '-');
	}

	++offset_x;
	draw_wrapper(render_x + 4 + offset_x, pos_y(), console::color::cyan, '[');
	++offset_x;
	draw_wrapper(render_x + 4 + offset_x, pos_y(), console::color::cyan, '[');

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
