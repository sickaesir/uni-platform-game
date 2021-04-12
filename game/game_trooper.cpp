#include "game_trooper.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"
#include "game_laser.hpp"

game::game_trooper::game_trooper(game_component* parent) : game_enemy(parent, game_component::component_type::trooper),
	jump_ticks(0)
{

}

void game::game_trooper::tick()
{
	descend_tick();
	move_tick();
	jump_tick();
	game_enemy::tick();
}

void game::game_trooper::jump_tick()
{
	if(get_tick_count() % get_game_settings()->get_enemy_movement_tick_interval()) return;

	if(!jump_ticks) return;

	for(int i = 0; i < get_enemy_width(); i++)
	{
		if(check_game_collision(pos_x() - get_game_map()->get_map_offset() + i, pos_y() - get_enemy_height() - 1))
		{
			log("found collision on top, aborting jump");
			jump_ticks = 0;
			return;
		}
	}

	pos_y(pos_y() - 1);
	jump_ticks--;
}

void game::game_trooper::descend_tick()
{
	if(get_tick_count() % get_game_settings()->get_enemy_movement_tick_interval() || jump_ticks) return;
	for(int i = 0; i < get_enemy_width(); i++)
		if(check_game_collision(pos_x() - get_game_map()->get_map_offset() + i, pos_y() + 1))
			return;

	pos_y(pos_y() + 1);
}

void game::game_trooper::move_tick()
{
	if(!(get_tick_count() % get_game_settings()->get_enemy_movement_tick_interval()))
	{
		int next_x = pos_x() + get_relative_character_x();

		bool move_collision = false;
		switch(get_relative_character_x())
		{
			case -1:
				//set_direction(game_component::direction_type::left);
				for(int y = pos_y() - get_enemy_height(); y < pos_y(); y++)
				{
					if(check_game_collision(next_x - get_game_map()->get_map_offset(), y))
					{
						move_collision = true;
						break;
					}
				}
			break;
			case 1:
				//set_direction(game_component::direction_type::right);
				for(int y = pos_y() - get_enemy_height(); y < pos_y(); y++)
				{
					if(check_game_collision(next_x + get_enemy_width() - get_game_map()->get_map_offset(), y))
					{
						move_collision = true;
						break;
					}
				}
			break;
		}

		if(!move_collision)
			pos_x(next_x);
	}

	if(can_shoot())
	{
		int shoot_x = pos_x();
		if(get_direction() != game_component::direction_type::left)
			shoot_x += get_enemy_width();

		//log("trooper laser initiated at x:%d y%d", laser->pos_x(), laser->pos_y());
		shoot(shoot_x, pos_y() - 1);
	}

	if(get_relative_character_y() == -1 && !jump_ticks)
	{
		bool ground_collision = false;

		for(int i = 0; i < get_enemy_width(); i++)
		{
			if(check_game_collision(pos_x() - get_game_map()->get_map_offset() + i, pos_y() + 1))
			{
				ground_collision = true;
				break;
			}
		}

		if(ground_collision)
			jump_ticks = 10;
	}
}

void game::game_trooper::render()
{
	switch(get_direction())
	{
		case game_component::direction_type::left:
			render_left();
		break;
		case game_component::direction_type::right:
			render_right();
		break;
	}

	game_enemy::render();
}

void game::game_trooper::render_right()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();
	auto draw_wrapper = [this](int x, int y, console::color color, char character) -> void {
		if(x < 0 || x > get_game_settings()->get_game_width())
			return;

		get_game_io()->draw(x, y, color, true, character);
	};

	int offset_x = 0;

	draw_wrapper(render_x + 3, pos_y() - 2, console::color::cyan, '(');
	draw_wrapper(render_x + 4, pos_y() - 2, console::color::cyan, ')');
	draw_wrapper(render_x + 5, pos_y() - 2, console::color::green, '=');
	draw_wrapper(render_x + 6, pos_y() - 2, console::color::green, '=');
	draw_wrapper(render_x + 7, pos_y() - 2, console::color::cyan, '(');
	draw_wrapper(render_x + 8, pos_y() - 2, console::color::cyan, ')');
	draw_wrapper(render_x + 4, pos_y() - 1, console::color::red, '/');
	draw_wrapper(render_x + 5, pos_y() - 1, console::color::white, '[');
	draw_wrapper(render_x + 6, pos_y() - 1, console::color::red, '>');

	if(pos_x() % 2)
	{
		draw_wrapper(render_x, pos_y(), console::color::cyan, ']');
		draw_wrapper(render_x + 1, pos_y(), console::color::cyan, ']');
		draw_wrapper(render_x + 2, pos_y(), console::color::magenta, '-');
		draw_wrapper(render_x + 3, pos_y(), console::color::magenta, '=');
	}
	else
	{
		draw_wrapper(render_x + 2, pos_y(), console::color::cyan, ']');
		draw_wrapper(render_x + 3, pos_y(), console::color::cyan, ']');
	}
	draw_wrapper(render_x + 4, pos_y(), console::color::cyan, ']');
	draw_wrapper(render_x + 5, pos_y(), console::color::cyan, '/');
	draw_wrapper(render_x + 6, pos_y(), console::color::cyan, '~');
	draw_wrapper(render_x + 7, pos_y(), console::color::magenta, '*');

}

void game::game_trooper::render_left()
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
}

unsigned int game::game_trooper::get_enemy_height()
{
	return 3;
}

unsigned int game::game_trooper::get_enemy_width()
{
	return 6;
}
