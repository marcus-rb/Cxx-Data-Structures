#pragma once

#include "..\core\custom_def.h"
#include "..\utility\memory.h"
#include "..\utility\iterator.h"

_CUSTOM_BEGIN_ // namespace custom {

template <typename vector_type>
class vector_iterator : public base_iterator<typename vector_type::T> {
public:
	using T_ptr = typename vector_type::T_ptr;
	using T_ref = typename vector_type::T_ref;
	using T = typename vector_type::T;

private:
	size_t m_index;
	T_ptr m_array_ptr;

public:
};

template <typename T, typename alloc_type = allocator<T>>
class vector {
public:
	using iterator = vector_iterator<vector<T, alloc_type>>;

	using T_ptr = T*;
	using T_ref = T&;

private:
	T_ptr m_data;
	size_t m_size;
	size_t m_capacity;

public:
	vector() : m_data(nullptr), m_size(0), m_capacity(0) noexcept {};

	vector(const size_t& initial_cap) : m_size(0) {
		m_data = new T[initial_cap];
		m_capacity = initial_cap;
	}
	// various methods
	T_ref operator=(const vector& other) {

	}

	T_ref assign() {
	}

	alloc_type get_allocator() {
		return 
	}

	// element access
	T_ref operator[](const size_t index) {
		return *(m_data + index);
	}

	// iterators
	iterator begin() {
		return iterator();
	}

	// capacity
	const size_t& size() const {
		return m_size;
	}
	// modifiers
	void zero() {
		memset(m_data, 0, sizeof(T) * m_capacity);
	}
};

template<typename alloc_type>
class vector<bool, alloc_type> {

};


_CUSTOM_END_