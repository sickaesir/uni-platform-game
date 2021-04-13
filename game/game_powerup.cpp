#include "game_powerup.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"
#include "game_character.hpp"
#include "game.hpp"

game::game_powerup::game_powerup(game_component* parent, powerup_type _type) :
	game_component(parent, game_component::component_type::powerup),
	type(_type),
	descend(true)
{
}

void game::game_powerup::tick()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();
	if(render_x >= 0 && render_x <= get_game_settings()->get_game_width() && descend && get_tick_count() % 50 == 0)
	{
		game_component* collided_component = check_game_collision(render_x, pos_y() + 3);
		if(!collided_component || collided_component->is_enemy())
			pos_y(pos_y() + 1);
		else
			descend = false;
	}
}

void game::game_powerup::render()
{
	char powerup_symbol = ' ';
	switch(type)
	{
		case powerup_type::heal:
			powerup_symbol = '+';
		break;
		case powerup_type::laser:
			powerup_symbol = '>';
		break;
		case powerup_type::jump:
			powerup_symbol = '^';
		break;
	}

	int render_x = pos_x() - get_game_map()->get_map_offset();

	if(render_x >= 0 && render_x <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x, pos_y(), console::color::yellow, true, '/');
		get_game_io()->draw(render_x, pos_y() + 1, console::color::green, true, get_tick_count() % 2 || !descend ? '|' : '-');
		get_game_io()->draw(render_x, pos_y() + 2, console::color::yellow, true, '\\');
	}

	if(render_x + 1 >= 0 && render_x + 1 <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x + 1, pos_y(), console::color::green, true, get_tick_count() % 2 || !descend ? '-' : '|');
		get_game_io()->draw(render_x + 1, pos_y() + 1, console::color::white, true, powerup_symbol);
		get_game_io()->draw(render_x + 1, pos_y() + 2, console::color::green, true, get_tick_count() % 2 || !descend ? '-' : '|');
	}

	if(render_x + 2 >= 0 && render_x + 2 <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x + 2, pos_y(), console::color::yellow, true, '\\');
		get_game_io()->draw(render_x + 2, pos_y() + 1, console::color::green, true, get_tick_count() % 2 || !descend ? '|' : '-');
		get_game_io()->draw(render_x + 2, pos_y() + 2, console::color::yellow, true, '/');
	}
}

game::game_powerup::powerup_type game::game_powerup::get_type()
{
	return type;
}

game::game_component* game::game_powerup::check_collision(game_component* requester, int x, int y)
{
	int render_x = pos_x() - get_game_map()->get_map_offset();
	if(render_x < 0 || render_x > get_game_settings()->get_game_width())
		return nullptr;

	if(y > pos_y()
		&& y < pos_y() + 2
		&& x > render_x
		&& x < render_x + 2)
		return this;

	return nullptr;
}

void game::game_powerup::pick()
{
	game_character* character = get_game_character();
	switch(get_type())
	{
		case powerup_type::heal:
			character->add_life(get_game_settings()->get_powerup_heal_amount());
		break;
		case powerup_type::laser:
			character->upgrade_laser();
		break;
		case powerup_type::jump:
			character->upgrade_jump();
		break;
	}

	get_game_instance()->add_points(get_game_settings()->get_powerup_points_increase());

	invalidate();
}
