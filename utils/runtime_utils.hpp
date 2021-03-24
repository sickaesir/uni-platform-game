#pragma once
#include "../common.hpp"

#define runtime_assert(expr, msg) { utils::runtime_utils::assert(expr, msg, __FILE__, __LINE__); }

namespace utils
{
	class runtime_utils
	{
	public:
		static inline int strlen(char* str)
		{
			int l = 0;
			while(true)
				if(!*(str++)) return l;
		}

		static inline void assert(bool expression, const char* message, const char* file, const char* line)
		{
			if(expression) return;

			std::cout << "assertion failed on " << file << ":" << line << " -> " << message << std::endl;

			// kill it
			int* p = 0;
			*p = 0;
		}
	};
}
