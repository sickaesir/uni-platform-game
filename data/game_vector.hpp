template<typename elem_t>
class game_vector {

public:
	game_vector();
	game_vector(unsigned int initial_size);
	~game_vector();

public:
	void resize(unsigned int new_allocated_size);
	void add(elem_t element);
	void remove_at(unsigned int index);

private:
	elem_t* vector_ptr;
	unsigned int size;
	unsigned int allocated_size;
};
