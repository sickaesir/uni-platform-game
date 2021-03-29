#pragma once
#include "../common.hpp"
#include "../data/data_vector.hpp"
#include "memory_utils.hpp"

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
			{
				if(!*(str++)) return l;
				l++;
			}
		}

		static inline int atoi(char* str)
		{
			int out = 0;
			int len = strlen(str);
			for(int i = 0; i < len; i++)
			{
				if(str[i] < '0' || str[i] > '9') return 0;
				out *= 10;
				out += (int)(str[i] - '0');
			}
			return out;
		}

		static inline bool strcmp(char* t1, char* t2)
		{
			int l1 = strlen(t1);
			int l2 = strlen(t2);
			if(l1 != l2)
				return false;

			for(int i = 0; i < l1; i++)
				if(t1[i] != t2[i])
					return false;
			return true;
		}

		static inline void str_split(char* str, char sep, data::data_vector<char*>& out_str)
		{
			int len = strlen(str);
			int split_start_idx = 0;
			int split_len = 0;
			for(int i = 0; i < len; i++)
			{
				if(str[i] == sep)
				{
					if(split_len == 0)
					{
						split_start_idx++;
						continue;
					}

					char* split = new char[split_len + 1];
					utils::memory_utils::memory_set_zero<char>(split, split_len + 1);
					utils::memory_utils::memory_copy<char>(split, str + split_start_idx, split_len);
					out_str.add(split);
					split_len = 0;
					split_start_idx = i + 1;
					continue;
				}
				split_len++;
			}

			if(split_len)
			{
				char* split = new char[split_len + 1];
				utils::memory_utils::memory_set_zero<char>(split, split_len + 1);
				utils::memory_utils::memory_copy<char>(split, str + split_start_idx, split_len);
				out_str.add(split);
			}
		}

		static inline void assert(bool expression, const char* message, const char* file, int line)
		{
			if(expression) return;
			nodelay(stdscr, false);
			erase();
			move(0, 0);
			attron(COLOR_PAIR(console::color::red));
			printw("assertion failed on %s:%d -> %s\n", file, line, message);
			while(true) getch();
		}
	};
}
