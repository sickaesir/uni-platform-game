#include "game_laser.hpp"
#include "../common.hpp"
#include "game_map.hpp"
#include "game_io.hpp"
#include "game_settings.hpp"
#include "../utils/runtime_utils.hpp"
#include "game.hpp"

game::game_laser::game_laser(game_component* parent, int laser_type,
		console::color laser_color /*= console::color::red*/,
		bool skip_rock_collision /*= false*/) :
	game_component(parent, game_component::component_type::laser),
	type(laser_type),
	collision_point({0, 0}),
	collided(false),
	color(laser_color),
	skip_rock(skip_rock_collision)
{
}

game::game_laser::~game_laser()
{

}

void game::game_laser::tick()
{
	if((get_direction() == game_component::direction_type::right
		&& pos_x() - get_game_map()->get_map_offset() > get_game_settings()->get_game_width())
		|| (get_direction() == game_component::direction_type::left
			&& pos_x() - get_game_map()->get_map_offset() + get_laser_length() < 0))
	{
		invalidate();
		log("laser went out of map, invalidating component");
		return;
	}
	if(collided)
	{
		if((get_direction() == game_component::direction_type::right
			&& pos_x() >= collision_point.x()) ||
			(get_direction() == game_component::direction_type::left
			&& pos_x() <= collision_point.x() - get_laser_length()))
		{
			invalidate();
			log("laser life ended, invalidating component");
		}
	}
	else
		check_laser_collision();

	if(get_game_instance()->get_tick_count() % 50 == 0)
	{
		switch(get_direction())
		{
			default:
			case game_component::direction_type::right:
				pos_x(pos_x() + 1);
			break;
			case game_component::direction_type::left:
				pos_x(pos_x() - 1);
			break;
		}
	}
}

void game::game_laser::check_laser_collision()
{
	int x = 0;
	switch(get_direction())
	{
		case game_component::direction_type::right:
			x = pos_x() + get_laser_length();
		break;
		case game_component::direction_type::left:
			x = pos_x();
		break;
	}

	game_component* collided_component = check_game_collision(x - get_game_map()->get_map_offset(), pos_y());
	if(!collided_component)
		return;

	if(collided_component->get_type() == game_component::component_type::rock && skip_rock)
		return;

	if(collided_component == get_parent() ||
		collided_component->get_type() == get_parent()->get_type())
		return;

	if(!collided)
	{
		collision_point.x(x);
		collision_point.y(pos_y());
		collided = true;
		log("laser_collided at x:%d y:%d on %s", collision_point.x(), collision_point.y(), collided_component->get_type_str());
	}
}

int game::game_laser::get_laser_index()
{
	int index = type * 2;
	if(get_direction() == game_component::direction_type::left)
		index += 1;
	return index;
}

int game::game_laser::get_laser_length()
{
	int index = get_laser_index();
	return utils::runtime_utils::strlen((char*)sprites::lasers[index]);
}

void game::game_laser::render()
{
	int laser_type = get_laser_index();

	for(int i = 0; i < get_laser_length(); i++)
	{
		int render_x = pos_x() + i;
		if(render_x - get_game_map()->get_map_offset() > get_game_settings()->get_game_width()
			|| render_x - get_game_map()->get_map_offset() < 0)
		{
			log("nlr 1");
			continue;
		}

		if(get_direction() == game_component::direction_type::right
			&& collided && render_x >= collision_point.x())
		{
			log("nlr 2");
			continue;
		}

		if(get_direction() == game_component::direction_type::left
			&& collided && render_x <= collision_point.x())
		{
			log("nlr 3");
			continue;
		}

		get_game_io()->draw(render_x - get_game_map()->get_map_offset(), pos_y(), color, true, sprites::lasers[get_laser_index()][i]);
	}
}
