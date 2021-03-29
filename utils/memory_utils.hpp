#pragma once

namespace utils
{
	class memory_utils {
	public:
		template<typename data_t>
		inline static void memory_copy(data_t* destination, data_t* source, int size, int destination_offset = 0, int source_offset = 0)
		{
			for(int i = 0; i < size; i++)
				*(destination + destination_offset + i) = *(source + source_offset + i);
		}

		template<typename data_t>
		inline static void memory_set(data_t* destination, const data_t& value, int count)
		{
			for(int i = 0; i < count; i++)
				destination[i] = value;
		}

		template<typename data_t>
		inline static void memory_set_zero(data_t* destination, int count)
		{
			for(int i = 0; i < count; i++)
				destination[i] = 0x00;
		}

		// sizeof(val_t) <= 4
		template<typename val_t>
		inline static unsigned int djb2_hash(const val_t& value)
		{
			unsigned int hash = 5381;
			const byte* value_bytes = reinterpret_cast<const byte*>(&value);

			for(int i = 0; i < sizeof(value); i++)
				hash = ((hash << 5) + hash) + value_bytes[i];

			return hash;
		}
	};
}
