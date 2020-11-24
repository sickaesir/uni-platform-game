#include "data/game_vector.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	game_vector<int> vector;
	for(int i = 0; i < 10; i++)
		vector.add(10 - i);

	vector.for_each([](const int& index, const int& elem) -> void {
		std::cout << index << " " << elem << std::endl;
	});

	vector.remove_at(0);

	std::cout << "______________________" << std::endl;

		vector.for_each([](const int& index, const int& elem) -> void {
			std::cout << index << " " << elem << std::endl;
		});

	return 0;
}
