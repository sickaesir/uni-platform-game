#include "game.hpp"

game::game::game() :
  running(true)
{
}

game::game::~game()
{
  running = false;
}

bool game::game::is_running()
{
  return running;
}


void game::game::tick()
{

}
