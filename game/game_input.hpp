#pragma once
#include "game_component.hpp"
namespace game
{
	class game_input : public game_component
	{
	public:
		game_input(game_component* parent);
		~game_input();

	public:
		virtual void render() override;
		virtual void tick() override;
		virtual bool on_keyboard(int character) override;
	};
}
