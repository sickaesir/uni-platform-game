class memory_utils {
	template<typename data_t>
	static void memory_copy(data_t* destination, data_t* source, unsigned int size, 
		unsigned int destination_offset = 0, unsigned int source_offset = 0);
};
