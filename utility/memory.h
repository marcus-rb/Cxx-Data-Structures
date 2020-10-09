#pragma once

#include "..\core\custom_def.h"
#include "utility_core.h"

_CUSTOM_BEGIN_

template <typename T>
constexpr size_t new_aligment = max<T>(alognof(T), _LIB_STANDARD_ALIGNMENT_);

#define _MEMORY_CORE_BEGIN_ namespace mem_core {
#define _MEMORY_CORE_END_ }

_MEMORY_CORE_BEGIN_

#define _LIB_STANDARD_ALIGNMENT_ 8U

template <typename T>
void deallocate(void* ptr, size_t amount = 1) {
	
	::operator delete(ptr, sizeof(T)*amount);
}

template <typename T>
T* allocate(size_t amount = 1) {
	return reinterpret_cast<T*>(::operator new(sizeof(T) * amount));
}

template <typename T>
const T* addressof(T& argument) noexcept {
	return __builtin_addressof(argument);
}

template <typename T>
const T* addressof(T&& arg) = delete;

_MEMORY_CORE_END_

#undef _MEMORY_CORE_BEGIN_
#undef _MEMORY_CORE_END_

template <typename T>
class allocator {
public:
	using from_primary = allocator;

	using valute_type = T;
	using T_ptr = T*;
	using T_ref = T&;

	T_ptr address(const T_ref value) noexcept {
		return mem_core::addressof(value);
	}
	const T_ptr address(const T_ref value) const noexcept {
		return mem_core::addressof(value);
	}

	void deallocate(T_ptr const ptr, const size_t& count) {
		mem_core::deallocate<T>(ptr, count);
	}

	T_ptr allocate(const size_t& amount) {
		mem_core::allocate<T>(amount);
	}
};

_CUSTOM_END_