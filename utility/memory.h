#pragma once

#include "..\core\custom_def.h"
#include "utility_core.h"
#include "type_traits.h"

_CUSTOM_BEGIN_


#define _MEMORY_CORE_BEGIN_ namespace mem_core {
#define _MEMORY_CORE_END_ }

_MEMORY_CORE_BEGIN_

#define _LIB_STANDARD_ALIGNMENT_ 8U

template <typename T>
constexpr size_t new_aligment = max<T>(alignof(T), _LIB_STANDARD_ALIGNMENT_);

template <typename T>
void deallocate(void* ptr, size_t amount = 1) {
	
	::operator delete(ptr, sizeof(T)*amount);
}

template <typename T>
T* allocate(size_t amount = 1) {
	return reinterpret_cast<T*>(::operator new(sizeof(T) * amount));
}

// need to add an is_object for the first criteria in enable_if. Should be is_object<T>::value and not "true"
template <typename T>
typename enable_if<true, T*>::type addressof(T& argument) noexcept {
	return reinterpret_cast<T*>(
		const_cast<char&>(
			reinterpret_cast<const volatile char&>(argument)
			)
		);
}

template <typename T>
typename enable_if<false, T*>::type addressof(T& argument) noexcept {
	return &argument;
}

// rvalues don't have addresses
template <typename T>
T* addressof(T&& arg) = delete;

// Interface for usage of custom allocators with the custom:: namespace containers.
template <typename T>
class base_allocator {
public:
	using T_ptr = T*;
	using T_ref = T&;

	virtual T_ptr address(const T_ref value) = 0;

	// memory methods should allocate for amount elements of type T
	virtual void deallocate(T_ptr const ptr, const size_t& count) = 0;
	virtual T_ptr allocate(const size_t& amount) = 0;
};

_MEMORY_CORE_END_ // namespace mem_core }

#undef _MEMORY_CORE_BEGIN_
#undef _MEMORY_CORE_END_

// default allocator CLASS TEMPLATE
template <typename T>
class allocator : public mem_core::base_allocator<T> {
public:

	using value_type = T;
	using T_ptr = T*;
	using T_ref = T&;

	static T_ptr address(T_ref value) noexcept {
		return mem_core::addressof<T>(value);
	}

	static void deallocate(T_ptr const ptr, const size_t& count) {
		mem_core::deallocate<T>(ptr, count);
	}

	static T_ptr allocate(const size_t& amount) {
		return mem_core::allocate<T>(amount);
	}
};

_CUSTOM_END_