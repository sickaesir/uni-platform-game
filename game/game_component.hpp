#pragma once
namespace game
{
	class game_component
	{
	public:
		game_component(game_component* parent, const char* name);
	public:
		virtual void render() = 0;
		virtual void tick() = 0;
		virtual bool on_keyboard(int character) = 0;
		void log(const char* format, ...);

	public:
		game_component* get_parent();
		class game_map* get_game_map();
		class game* get_game_instance();

	private:
		game_component* parent_component;
		const char* component_name;
	};
}
