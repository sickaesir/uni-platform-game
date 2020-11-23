#include "game_vector.hpp"
#include "../utils/memory_utils.hpp"
#include "../utils/math_utils.hpp"

template<typename elem_t>
game_vector<elem_t>::game_vector()
{
	vector_ptr = new elem_t[0];
	size = allocated_size = 0;
	resize(10);
}

template<typename elem_t>
game_vector<elem_t>::~game_vector()
{
	delete[] vector_ptr;
}

template<typename elem_t>
game_vector<elem_t>::game_vector(unsigned int initial_size) : game_vector()
{
	resize(initial_size);
}

template<typename elem_t>
void game_vector<elem_t>::resize(unsigned int new_allocated_size)
{
	elem_t* vector_backup = new elem_t[allocated_size];
	memory_utils::memory_copy(vector_backup, vector_ptr, allocated_size);

	delete[] vector_ptr;
	vector_ptr = new elem_t[new_allocated_size];
	unsigned int preserved_elements = math_utils::min(allocated_size, new_allocated_size);
	memory_utils::memory_copy(vector_ptr, vector_backup, preserved_elements);
	allocated_size = new_allocated_size;
	size = math_utils::min(size, allocated_size);
	delete[] vector_backup;
}

template<typename elem_t>
void game_vector<elem_t>::add(elem_t element)
{
	if(size >= allocated_size - 1)
		resize(allocated_size + (allocated_size / 2));

	vector_ptr[size++] = element;
}

template<typename elem_t>
void game_vector<elem_t>::remove_at(unsigned int index)
{
	for(int i = index; i < size - 1; i++)
		vector_ptr[i] = vector_ptr[i + 1];
	size--;
}
