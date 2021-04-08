#pragma once
#include "game_component.hpp"

namespace game
{
	class game_laser : public game_component
	{
	public:
		game_laser(game_component* parent, int laser_type);
		~game_laser();

	public:
		virtual void tick() override;
		virtual void render() override;
		int get_laser_length();

	private:
		int get_laser_index();

	private:
		int type;
		data::data_point collision_point;
		bool collided;
	};
};
