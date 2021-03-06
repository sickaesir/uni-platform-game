#include "game_flyier.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"

game::game_flyier::game_flyier(game_component* parent) : game_enemy(parent, game_component::component_type::flyier)
{

}

void game::game_flyier::tick()
{
	move_tick();
	shoot_tick();
	game_enemy::tick();
}

void game::game_flyier::shoot_tick()
{
	if(!can_shoot())
		return;

	int shoot_x = pos_x() + 10;
	if(get_direction() != game_component::direction_type::left)
		shoot_x += 3;

	shoot(shoot_x, pos_y() - get_laser_y_offset());
}

void game::game_flyier::move_tick()
{
	if(get_tick_count() % get_game_settings()->get_enemy_movement_tick_interval())
		return;

	int next_x = pos_x() + get_relative_character_x();
	int next_y = pos_y() + get_relative_character_y();

	game_component* collision_component = nullptr;
	switch(get_relative_character_x())
	{
		case -1:
			for(int y = pos_y() - get_enemy_height(); y < pos_y(); y++)
			{
				game_component* collided_component = nullptr;
				if((collided_component = check_game_collision(next_x - get_game_map()->get_map_offset(), y)) &&
					collided_component->is_enemy())
					return;
			}
		break;

		case 1:
			for(int y = pos_y() - get_enemy_height(); y < pos_y(); y++)
			{
				game_component* collided_component = nullptr;
				if((collided_component = check_game_collision(next_x + get_enemy_width()
						 - get_game_map()->get_map_offset(), y)) &&
					collided_component->is_enemy())
					return;
			}
		break;
	}

	pos_x(next_x);
	pos_y(next_y);
}

void game::game_flyier::render()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();

	auto draw_wrapper = [this](int x, int y, console::color color, char character) -> void {
		if(x < 0 || x > get_game_settings()->get_game_width())
			return;

		get_game_io()->draw(x, y, color, true, character);
	};

	// left left-most fan
	draw_wrapper(render_x, pos_y() - 4, console::color::white, get_tick_count() % 3 ? '=' : '-');
	draw_wrapper(render_x + 1, pos_y() - 4, console::color::white, get_tick_count() % 4 ? '=' : '-');
	draw_wrapper(render_x + 2, pos_y() - 4, console::color::white, get_tick_count() % 5 ? '=' : '-');
	draw_wrapper(render_x + 3, pos_y() - 4, console::color::white, get_tick_count() % 6 ? '=' : '-');

	// left fan pivot
	draw_wrapper(render_x + 4, pos_y() - 4, console::color::cyan, get_tick_count() % 7 ? ':' : '*');

	// left right-most fan
	draw_wrapper(render_x + 5, pos_y() - 4, console::color::white, get_tick_count() % 3 ? '=' : '-');
	draw_wrapper(render_x + 6, pos_y() - 4, console::color::white, get_tick_count() % 4 ? '=' : '-');
	draw_wrapper(render_x + 7, pos_y() - 4, console::color::white, get_tick_count() % 5 ? '=' : '-');
	draw_wrapper(render_x + 8, pos_y() - 4, console::color::white, get_tick_count() % 6 ? '=' : '-');

	// right left-most fan
	draw_wrapper(render_x + 17, pos_y() - 4, console::color::white, get_tick_count() % 3 ? '=' : '-');
	draw_wrapper(render_x + 18, pos_y() - 4, console::color::white, get_tick_count() % 4 ? '=' : '-');
	draw_wrapper(render_x + 19, pos_y() - 4, console::color::white, get_tick_count() % 5 ? '=' : '-');
	draw_wrapper(render_x + 20, pos_y() - 4, console::color::white, get_tick_count() % 6 ? '=' : '-');

	// right fan pivot
	draw_wrapper(render_x + 21, pos_y() - 4, console::color::cyan, get_tick_count() % 7 ? ':' : '*');

	// right right-most fan
	draw_wrapper(render_x + 22, pos_y() - 4, console::color::white, get_tick_count() % 3 ? '=' : '-');
	draw_wrapper(render_x + 23, pos_y() - 4, console::color::white, get_tick_count() % 4 ? '=' : '-');
	draw_wrapper(render_x + 24, pos_y() - 4, console::color::white, get_tick_count() % 5 ? '=' : '-');
	draw_wrapper(render_x + 25, pos_y() - 4, console::color::white, get_tick_count() % 6 ? '=' : '-');


	// fan pivot sustain
	draw_wrapper(render_x + 4, pos_y() - 3, console::color::green, 'I');
	draw_wrapper(render_x + 21, pos_y() - 3, console::color::green, 'I');

	// left eye
	draw_wrapper(render_x + 9, pos_y() - 3, console::color::white, '[');
	draw_wrapper(render_x + 10, pos_y() - 3, console::color::red, 'o');
	draw_wrapper(render_x + 11, pos_y() - 3, console::color::white, ']');

	// right eye
	draw_wrapper(render_x + 14, pos_y() - 3, console::color::white, '[');
	draw_wrapper(render_x + 15, pos_y() - 3, console::color::red, 'o');
	draw_wrapper(render_x + 16, pos_y() - 3, console::color::white, ']');

	draw_wrapper(render_x + 3, pos_y() - 2, console::color::white, '/');
	draw_wrapper(render_x + 4, pos_y() - 2, console::color::green, ':');
	draw_wrapper(render_x + 5, pos_y() - 2, console::color::white, '\\');
	draw_wrapper(render_x + 6, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 7, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 8, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 9, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 10, pos_y() - 2, console::color::white, '\\');
	draw_wrapper(render_x + 11, pos_y() - 2, console::color::white, '\\');
	draw_wrapper(render_x + 12, pos_y() - 2, console::color::white, '_');
	draw_wrapper(render_x + 13, pos_y() - 2, console::color::white, '_');
	draw_wrapper(render_x + 14, pos_y() - 2, console::color::white, '/');
	draw_wrapper(render_x + 15, pos_y() - 2, console::color::white, '/');
	draw_wrapper(render_x + 16, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 17, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 18, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 19, pos_y() - 2, console::color::white, '-');
	draw_wrapper(render_x + 20, pos_y() - 2, console::color::white, '/');
	draw_wrapper(render_x + 21, pos_y() - 2, console::color::green, ':');
	draw_wrapper(render_x + 22, pos_y() - 2, console::color::white, '\\');

	draw_wrapper(render_x + 3, pos_y() - 1, console::color::white, '\\');
	draw_wrapper(render_x + 4, pos_y() - 1, console::color::green, '\'');
	draw_wrapper(render_x + 5, pos_y() - 1, console::color::white, '/');
	draw_wrapper(render_x + 6, pos_y() - 1, console::color::cyan, '>');
	draw_wrapper(render_x + 7, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 8, pos_y() - 1, console::color::white, 'T');
	draw_wrapper(render_x + 9, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 10, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 11, pos_y() - 1, console::color::white, '!');
	draw_wrapper(render_x + 12, pos_y() - 1, console::color::green, '>');
	draw_wrapper(render_x + 13, pos_y() - 1, console::color::green, '<');
	draw_wrapper(render_x + 14, pos_y() - 1, console::color::white, '!');
	draw_wrapper(render_x + 15, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 16, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 17, pos_y() - 1, console::color::white, 'T');
	draw_wrapper(render_x + 18, pos_y() - 1, console::color::white, '-');
	draw_wrapper(render_x + 19, pos_y() - 1, console::color::cyan, '<');
	draw_wrapper(render_x + 20, pos_y() - 1, console::color::white, '\\');
	draw_wrapper(render_x + 21, pos_y() - 1, console::color::green, '\'');
	draw_wrapper(render_x + 22, pos_y() - 1, console::color::white, '/');

	if(get_direction() == game_component::direction_type::left)
	{
		draw_wrapper(render_x + 11, pos_y(), console::color::red, '<');
		draw_wrapper(render_x + 12, pos_y(), console::color::white, ']');
		draw_wrapper(render_x + 13, pos_y(), console::color::red, '\\');
	}
	else
	{
		draw_wrapper(render_x + 11, pos_y(), console::color::red, '/');
		draw_wrapper(render_x + 12, pos_y(), console::color::white, '[');
		draw_wrapper(render_x + 13, pos_y(), console::color::red, '>');
	}

	game_enemy::render();
}

unsigned int game::game_flyier::get_enemy_height()
{
	return 5;
}

unsigned int game::game_flyier::get_enemy_width()
{
	return 25;
}

unsigned int game::game_flyier::get_laser_y_offset()
{
	return 0;
}
