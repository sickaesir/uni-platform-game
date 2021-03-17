#pragma once
#include "game_component.hpp"

namespace game
{
	class game_character : public game_component
	{
	public:
		game_character();
		~game_character();

	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int character) override;
	};
}
