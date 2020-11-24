#pragma once
#include "../utils/memory_utils.hpp"
#include "../utils/math_utils.hpp"

template<typename elem_t>
class game_vector {

public:
	game_vector()
	{
			vector_ptr = new elem_t[0];
			size = allocated_size = 0;
			resize(10);
	}


	game_vector(int initial_size) : game_vector()
	{
		resize(initial_size);
	}


	~game_vector()
	{
			delete[] vector_ptr;
	}

public:
	void resize(int new_allocated_size)
	{
		elem_t* vector_backup = new elem_t[allocated_size];
		memory_utils::memory_copy<elem_t>(vector_backup, vector_ptr, allocated_size);

		delete[] vector_ptr;
		vector_ptr = new elem_t[new_allocated_size];
		int preserved_elements = math_utils::min(allocated_size, new_allocated_size);
		memory_utils::memory_copy<elem_t>(vector_ptr, vector_backup, preserved_elements);
		allocated_size = new_allocated_size;
		size = math_utils::min<int>(size, allocated_size);
		delete[] vector_backup;
	}


	void add(elem_t element)
	{
		if(size >= allocated_size - 1)
			resize(allocated_size + (allocated_size / 2));

		vector_ptr[size++] = element;
	}


	void remove_at(int index)
	{
		for(int i = index; i < size - 1; i++)
			vector_ptr[i] = vector_ptr[i + 1];
		size--;
	}

	void for_each(void(*func)(const int&, const elem_t&))
	{
		for(int i = 0; i < size; i++)
			func(i, vector_ptr[i]);
	}

private:
	elem_t* vector_ptr;
	int size;
	int allocated_size;
};
