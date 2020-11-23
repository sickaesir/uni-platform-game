#include "memory_utils.hpp"

template<typename data_t>
void memory_utils::memory_copy(data_t* destination, data_t* source, unsigned int size,
	unsigned int destination_offset /*= 0*/, unsigned int source_offset /*= 0*/)
{
	for(unsigned int i = 0; i < size; i++)
		*(destination + destination_offset + i) = *(source + source_offset + i);
}
