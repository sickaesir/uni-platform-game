#pragma once
namespace utils
{
	class math_utils
	{
	public:
		template<typename num_t>
		inline static num_t min(const num_t& a1, const num_t& a2)
		{
			return a1 < a2 ? a1 : a2;
		}

		template<typename num_t>
		inline static num_t max(const num_t& a1, const num_t& a2)
		{
			return a1 > a2 ? a1 : a2;
		}
	};
}
