#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"

game::game::game() :
	running(true)
	//map(new game_map())
{
	components = new data::data_vector<game_component*>();
	components->add(new game_map());
}

game::game::~game()
{
	running = false;
	components->for_each([](int idx, game_component* component) {
		delete component;
	});
	delete components;
}

bool game::game::is_running()
{
	return running;
}


void game::game::tick()
{
	components->for_each([](int idx, game_component* component) {
		if(component)
			component->tick();
	});
}

void game::game::render()
{
	std::cout << console_code::reset_cursor_position << console_code::hide_cursor;
	components->for_each([](int idx, game_component* component) {
		if(component)
			component->render();
	});
}
