#pragma once
#include "game_component.hpp"
namespace game
{
	class game_io : public game_component
	{
	public:
		game_io(game_component* parent);
		~game_io();

	public:
		virtual void render() override;
		virtual void tick() override;
		virtual bool on_keyboard(int character) override;

	public:
		void clear_screen();
		void draw(int x, int y, console::color color, bool bright, const char* format, ...);

	private:
		void init_colors();
	};
}
