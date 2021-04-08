#pragma once
#include "game_component.hpp"

namespace game
{
	class game_powerup : public game_component
	{
	public:
		enum class powerup_type
		{
			heal = 0,
			_last
		};
	public:
		game_powerup(game_component* parent, powerup_type _type);

	public:
		virtual void render() override;
		virtual void tick() override;

	private:
		powerup_type type;
		bool descend;
	};
};
