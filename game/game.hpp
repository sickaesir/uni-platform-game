#pragma once

namespace game
{
  class game_map;
  class game
  {
  public:
    game();
    ~game();

  // getters
  public:
    bool is_running();

  // public methods
  public:
    void tick();
    void render();


  private:
    bool running;
    game_map* map;
  };

}
