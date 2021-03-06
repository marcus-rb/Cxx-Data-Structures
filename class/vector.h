#pragma once

// [ ] implicit vector iterator

#include "..\core\custom_def.h"
#include "..\utility\memory.h"
#include "..\utility\iterator.h"

_CUSTOM_BEGIN_ // namespace custom {

#define _VECTOR_REALLOCATE_RATIO_ 1
#define _CLEAN_VECTOR_MEMORY_ 1

template <typename vector_type>
class vector_iterator : public custom::base_iterator<typename vector_type::value_type, custom::vector_iterator<vector_type>> {
public:
	using T_ptr = typename vector_type::T_ptr;
	using T_ref = typename vector_type::T_ref;

	using value_type = typename vector_type::value_type;

private:
	size_t m_index;
	T_ptr m_array_ptr;

public:
	vector_iterator() : m_index(0), m_array_ptr(nullptr) noexcept {};
	vector_iterator(T_ptr array_ptr, const size_t& index) {
		m_index = index;
		m_array_ptr = array_ptr;
	}

	vector_iterator(vector_type& vec, const size_t& index) {
		m_index = index;
		m_array_ptr = vec.m_data;
	}

	T_ref operator*() {
		return *operator->();
	}

	T_ptr operator->() {
		return m_array_ptr+m_index;
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

	const size_t& get_index() const {
		return m_index;
	}

	friend vector_type;
};

template <typename T, typename alloc = custom::allocator<T>>
class vector {
public:

	using iterator = custom::vector_iterator<vector<T, alloc>>;
	using value_type = T;

	using T_ptr = T*;
	using T_ref = T&;

	using const_T_ref = const T&;
	using const_T_ptr = const T*;

private:

	struct local_allocator {
		T_ptr (*allocate)(const size_t&) = alloc::allocate;
		void (*deallocate)(T_ptr const, const size_t&) = alloc::deallocate;
		T_ptr (*address)(T_ref) = alloc::address;
	};

	T_ptr m_data;
	size_t m_size;
	size_t m_capacity;

public:
	vector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {};

	vector(const size_t& initial_cap) : m_size(initial_cap), m_capacity(initial_cap) {
		m_data = alloc::allocate(m_capacity);
	}

	vector(const vector& other) {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = alloc::allocate(other.m_capacity);
		for (size_t i = 0; i < m_size; i++)
			(*m_data + i) = (*other.m_data + i);
	}

	vector(vector&& other) {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		other.m_data = nullptr;
	}

	vector& operator=(const vector& other) {
	#if _CLEAN_VECTOR_MEMORY_
		clean_vector();
	#endif
		alloc::deallocate(m_data, m_capacity);

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;
	}

	vector& operator=(vector&& other) {
	#if _CLEAN_VECTOR_MEMORY_
		clean_vector();
	#endif
		alloc::deallocate(m_data, m_capacity);
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
	}

	~vector() {
		alloc::deallocate(m_data, m_capacity);
	}

	local_allocator get_allocator() {
		return local_allocator();
	}

	// -- ELEMENT ACCESS --
	T_ref operator[](const size_t index) {
		return *(m_data + index);
	}

	T_ref at(const size_t index) {
		index > m_size - 1 ? __debugbreak() : NULL;
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
		return m_size == 0;
	}

	T_ptr shrink_to_fit() {
	#if _CLEAN_VECTOR_MEMORY_
		for (size_t i = m_size; i < m_capacity; i++) {
			*(m_data + i) = 0;
		}
	#endif
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
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = 0;
		}
	}
	void clear() {
		zero();
	}

	iterator push_back(const T& value) {
		if (m_capacity > m_size) {
			*(m_data + m_size) = value;
			m_size++;
		}
		else {
			increase_capacity();
			push_back(value);
		}
		return iterator(m_data, m_size - 1);
	}

	iterator push_back(T&& value) {
		return push_back((const T&)value);
	}

	template<typename... arguments>
	iterator emplace_back(arguments&&... args) {
		return push_back(T(args...));
	}

	template<typename... arguments>
	iterator emplace(const size_t& position, arguments&&... args) {
		insert(position , T(args));
	}

	iterator insert(const size_t& position, const T& value) {
		// If m_capacity > m_size, no reallocation is needed
		if (m_capacity > m_size) {
			for (size_t i = m_size; i > position; i--) {
				*(m_data + i - 1) = *(m_data + i - 2);
			}
			m_data[position] = value;
			m_size++;
		}
		else {
			increase_capacity();
			insert(position, value);
		}

		return iterator(m_data, position);
	}

	iterator erase(const size_t& position) {
		erase(iterator(m_data, position));
	}
	iterator erase(iterator position) {
		for (; position != this->end(); ++position) {
			*(m_data + position) = *(m_data + position - 1);
		}
	}

	iterator erase(const size_t& first, const size_t& last) {
		return erase(iterator(m_data, first), iterator(m_data, last));
	}
	iterator erase(iterator first, iterator last) {
	#if _CLEAN_VECTOR_MEMORY_
		++last;
		for (auto it = first; it != last; ++it) {
			*it = 0;
		}
		--last;
	#endif

		size_t amount_of_elements_to_delete = last.get_index() - first.get_index() + 1;
		size_t i = 0;
		while (i < m_size && i < amount_of_elements_to_delete) { // We cannot take elements from past the end of array when deleting

			*(m_data + first.get_index() + i) = *(m_data + last.get_index() + 1 + i);
			i++;
		}
		m_size -= amount_of_elements_to_delete;
		return iterator(m_data, first.get_index());
	}

	iterator pop_back() {
		m_size--;
	#if _CLEAN_VECTOR_MEMORY_
		m_data[m_size] = NULL;
	#endif
		return this->end();
	}

	void resize(const size_t& count) {
		if (count > m_capacity) {
			increase_capacity();
			resize(count);
		}
		else {
			#if _CLEAN_VECTOR_MEMORY_
			if (m_size > count) {
				erase(iterator(m_data, count), this->end());
			}
			#endif
			m_size = count;
		}
	}

	void swap(vector& other) {
		if (m_capacity >= other.m_size && other.m_capacity >= m_size) {
			unsigned int largest = other.m_size > m_size ? other.m_size : m_size;
			for (size_t i = 0; i < largest; i++) {
				T temp = *(m_data + i);
				*(m_data + i) = *(other.m_data + i);
				*(other.m_data + i) = temp;
			}
			size_t temp_size = m_size;
			m_size = other.m_size;
			other.m_size = temp_size;

		#if _CLEAN_VECTOR_MEMORY_
			for (auto it = this->end(); it.m_index != m_capacity; ++it) {
				*it = 0;
			}
			for (auto it = other.end(); it.m_index != other.m_capacity; ++it) {
				*it = 0;
			}
		#endif
		}
		else {
			// ERROR: vectors cannot be swapped
		}

	}

private:
	void increase_capacity() {

		if (m_capacity == 0) // Prevent recursive calls if this is the first increase
			m_capacity = 1;

	#if _VECTOR_REALLOCATE_RATIO_ <= 1
		reallocate(m_capacity + m_capacity * _VECTOR_REALLOCATE_RATIO_);
	#else 
		reallocate(m_capacity * _VECTOR_REALLOCATE_RATIO_);
	#endif
	}

	void clean_vector() {

		// destroy_and_clean determines wether or not T is an object-type
		for (size_t i = 0; i < m_size; i++) {
			mem_core::destroy_and_clean<T>(m_data + i);
		}

	}

	void reallocate(size_t new_capacity) {

		T_ptr new_pos = alloc::allocate(new_capacity);
		for (size_t i = 0; i < m_size; i++)
			*(new_pos + i) = *(m_data + i);
		alloc::deallocate(m_data, m_capacity);
		m_data = new_pos;
		m_capacity = new_capacity;
	}
};

_CUSTOM_END_

template<typename T, typename alloc = custom::allocator<T>>
bool operator==(custom::vector<T, alloc>& lhs, custom::vector<T, alloc>& rhs) {
	size_t return_signal = 0;
	if (lhs.size() == rhs.size()) {
		for (size_t i = 0; i < lhs.size(); i++)
			lhs[i] == rhs[i] ? NULL : return_signal++;
		return return_signal ? false : true;
	}
	else {
		return false;
	}
}
