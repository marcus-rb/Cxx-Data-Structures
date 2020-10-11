#pragma once

// TODO
// [ ] reverse iterators

#include "..\core\custom_def.h"
#include "..\utility\iterator.h"

_CUSTOM_BEGIN_ // namespace custom {

template<typename array_type>
class array_iterator : public base_iterator<typename array_type::value_type, array_iterator<array_type>> {
public:
	using T_ptr = typename array_type::T_ptr;
	using T_ref = typename array_type::T_ref;
	using T = typename array_type::value_type;

private:
	size_t m_index;
	T_ptr m_array_ptr;

public:
	array_iterator() : array_ptr(), m_index(0) {}
	explicit array_iterator(T_ptr array, size_t offset = 0) : m_index(offset), m_array_ptr(array) {}

	T_ref operator*() {
		return *operator->();
	}

	T_ptr operator->() {
		return m_array_ptr + m_index;
	}

	array_iterator& operator++() {
		++m_index;
		return *this;
	}

	array_iterator operator++(int) {
		array_iterator temp = *this;
		++(*this);
		return temp;
	}

	array_iterator& operator--() {
		m_index--;
		return *this;
	}

	array_iterator operator--(int) {
		array_iterator temp = *this;
		--(*this);
		return temp;
	}

	bool operator==(array_iterator& other) {
		return m_index == other.m_index && m_array_ptr == other.m_array_ptr;
	}

	bool operator!=(array_iterator& other) {
		return !operator==(other);
	}
};

template <typename T, size_t S>
class array {
public:
	using iterator = custom::array_iterator<array<T, S>>;

	using T_ref = T&;
	using T_ptr = T*;

	using value_type = T;
private:
	T m_data[S];

public:
	// element access
	T_ptr data() {
		return m_data;
	}
	const T_ptr data() const {
		return m_data;
	}

	T_ref back() {
		return m_data[S - 1];
	}
	const T_ref back() const {
		return m_data[S - 1];
	}

	T_ref front() {
		return m_data[0];
	}
	const T_ref front() const {
		return m_data[0];
	}

	T_ref at(const size_t& index) {
		index > S - 1 ? NULL : __debugbreak();
		return m_data[index];
	}
	const T_ref at(const size_t& index) const {
		index > S - 1 ? NULL : __debugbreak();
		return m_data[index];
	}

	T_ref operator[] (const size_t& index) {
		return m_data[index];
	}
	const T_ref operator[](const size_t& index) const {
		return m_data[index];
	}

	// iterators
	iterator begin() {
		return iterator(m_data, 0);
	}

	iterator end() {
		return iterator(m_data, S);
	}

	// capacity
	constexpr size_t size() const {
		return S;
	}
	constexpr size_t max_size() const {
		return S;
	}
	constexpr size_t empty() const {
		return S == 0;
	}

	//operations
	void fill(const T& value) {
		for (size_t i = 0; i < S; ++i) m_data[i] = value;
	}
	void fill(T&& value) {
		for (size_t i = 0; i < S; ++i) m_data[i] = value;
	}
	void swap(const array& other) {
		// Implement some form of safety check here?
		for (size_t i = 0; i < S; ++i) {
			static T temp;
			temp = other.m_data[i];
			other.m_data[i] = m_data[i];
			m_data[i] = temp;
		}
	}
};

_CUSTOM_END_