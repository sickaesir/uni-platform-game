#pragma once
#include "../common.h"

#define runtime_assert(expr, msg) { utils::runtime_utils::assert(expr, msg, __FILE__, __LINE__); }

namespace utils
{
  class runtime_utils
  {
    inline void assert(bool expression, const char* message, const char* file, const char* line)
    {
      if(expression) return;

      std::cout <<
    }
  }
}
