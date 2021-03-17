#pragma once
namespace game
{
	class game_component
	{
	public:
		virtual void render() = 0;
		virtual void tick() = 0;
		virtual bool on_keyboard(int character) = 0;
	};
}
