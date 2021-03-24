#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"
#include "game_input.hpp"

game::game::game() : game_component(nullptr),
	running(true)
{
	map = new game_map(this);
	input = new game_input(this);
	components.add(map);
	components.add(input);
}

game::game::~game()
{
	running = false;
	components.for_each([](int idx, game_component* component) {
		delete component;
	});

	components.resize(0);

	// those gets deleted along with the components
	map = nullptr;
	input = nullptr;
}

bool game::game::is_running()
{
	return running;
}

bool game::game::on_keyboard(int keyboard_key)
{
	for(int i = 0; i < components.get_size(); i++)
		if(components[i] && components[i]->on_keyboard(keyboard_key))
			break;
	return true;
}

void game::game::tick()
{
	components.for_each([](int idx, game_component* component) {
		if(component)
			component->tick();
	});
}

void game::game::render()
{
	std::cout << console_code::reset_cursor_position << console_code::hide_cursor;
	components.for_each([](int idx, game_component* component) {
		if(component)
			component->render();
	});
}
