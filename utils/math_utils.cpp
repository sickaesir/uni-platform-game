#include "math_utils.hpp"

template<typename num_t>
num_t math_utils::min(const num_t& a1, const num_t& a2)
{
	if(a1 < a2) return a1;
	return a2;
}

template<typename num_t>
num_t math_utils::max(const num_t& a1, const num_t& a2)
{
	if(a1 > a2) return a1;
	return a2;
}
