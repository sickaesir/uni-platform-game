#pragma once
#include "game_component.hpp"
namespace game
{
	class game_menu : public game_component
	{
	public:
		game_menu(game_component* parent);


	public:
		virtual void render();
	};
};
