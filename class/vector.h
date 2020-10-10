#pragma once

#include "..\core\custom_def.h"
#include "..\utility\memory.h"
#include "..\utility\iterator.h"

_CUSTOM_BEGIN_ // namespace custom {

#define _VECTOR_REALLOCATE_RATIO_ 1

template <typename vector_type>
class vector_iterator : public base_iterator<typename vector_type::value_type> {
public:
	using T_ptr = typename vector_type::T_ptr;
	using T_ref = typename vector_type::T_ref;

private:
	size_t m_index;
	T_ptr m_array_ptr;

public:
	vector_iterator() : m_index(0), m_array_ptr(nullptr) noexcept {};
	vector_iterator(T_ptr array_ptr, size_t index) {
		m_index = index;
		m_array_ptr = array_ptr;
	}

	T_ref operator*() {
		return *operator->();
	}

	T_ptr operator->() {
		return m_array_ptr+index;
	}

	vector_iterator& operator++() {
		++m_index;
		return *this;
	}

	vector_iterator operator++(int) {
		vector_iterator temp = *this;
		++m_index;
		return temp;
	}

	vector_iterator& operator--() {
		--m_index;
		return *this;
	}
	vector_iterator operator--(int) {
		vector_iterator temp = *this;
		--m_index;
		return temp;
	}

	bool operator==(vector_iterator& other) {
		return m_array_ptr == other.m_array_ptr && m_index == other.m_index;
	}
	bool operator!=(vector_iterator& other) {
		return !operator==(other);
	}
};

template <typename T, typename alloc = allocator<T>>
class vector {
public:

	using iterator = vector_iterator<vector<T, alloc>>;

	using T_ptr = T*;
	using T_ref = T&;

	using value_type = T;
private:
	T_ptr m_data;
	size_t m_size;
	size_t m_capacity;
public:
	vector() : m_data(nullptr), m_size(0), m_capacity(0) noexcept {};

	vector(const size_t& initial_cap) : m_size(0) {
		m_data = alloc::allocate(m_capacity);
		m_capacity = initial_cap;
	}

	vector(const vector& other) {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = alloc::allocate(other.m_capacity);
		memcpy(m_data, other.m_data, m_capacity);
	}

	~vector() {
		alloc::deallocate(m_data, m_capacity);
	}

	// -- ELEMENT ACCESS --
	T_ref operator[](const size_t index) {
		return *(m_data + index);
	}

	T_ref at(const size_t index) {
		index > m_size - 1 : __debugbreak() : NULL;
		return *(m_data + index);
	}

	T_ref front() {
		return *m_data;
	}

	T_ref back() {
		return *(m_data + m_size - 1);
	}

	T_ptr data() {
		return m_data;
	}

	// -- ITERATORS --
	iterator begin() {
		return iterator(m_data, 0);
	}
	iterator end() {
		return iterator(m_data, m_size);
	}

	// -- CAPACITY --
	bool empty() const {
		return m_size ? false : true;
	}

	T_ptr shrink_to_fit() {
		realloc(m_data, sizeof(T) * m_size);
		m_capacity = m_size;
	}

	void reserve(const size_t& new_capacity) {
		if (new_capacity > m_capacity) {
			reallocate(new_capacity);
		}
	}

	const size_t& size() const {
		return m_size;
	}

	const size_t& capacity() const {
		return m_capacity;
	}

	// -- MODIFIERS --
	void zero() {
		memset(m_data, 0, sizeof(T) * m_capacity);
	}
	void clear() {
		zero();
	}

	iterator insert(const size_t& position, const T& value) {
		// If m_capacity > m_size, no reallocation is needed
		if (m_capacity > m_size) {
			for (size_t i = m_size; i > position; i--) {
				*(m_data + i - 1) = *(m_data + i - 2);
			}
			m_data[position] = value;
		}
		else {
			// this could be optimized but I can't be bothered. This is way easier
			reallocate(m_capacity * _VECTOR_REALLOCATE_RATIO_);
		}

		return iterator(m_data, position);
	}

private:
	void reallocate(size_t new_capacity) {
		// 1. allocate a new block of memory
		T_ptr new_pos = alloc::allocate(new_capacity);
		memcpy(new_pos, m_data, m_size);
		alloc::deallocate(m_data, m_capacity);
		m_data = new_pos;
		m_capacity = new_capacity;
	}
};

_CUSTOM_END_

custom::vector<int> test_vector(10);

