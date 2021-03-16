#pragma once
namespace game
{
	class game_map
	{
	public:
		game_map();
		~game_map();

	// public getters
	public:
		int height();
		int width();

	// public methods
	public:
		void tick();
		void render(int start_from_offset);

 	private:
		void extend_map();

	private:
		char** map_text;
		int map_height;
		int map_width;
	};
}
