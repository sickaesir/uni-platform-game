#pragma once
namespace utils
{
	class meta_utils {
	public:
		template<typename T>
		struct is_pointer { static const bool value = false; };

		template<typename T>
		struct is_pointer<T*> { static const bool value = true; };
	};
};
