#pragma once
namespace game
{
	class game_component
	{
	public:
		game_component(game_component* parent);
	public:
		virtual void render() = 0;
		virtual void tick() = 0;
		virtual bool on_keyboard(int character) = 0;

	public:
		game_component* get_parent();

	private:
		game_component* parent_component;
	};
}
