#pragma once

#include "..\core\custom_def.h"

_CUSTOM_BEGIN_

template <typename T, size_t N>
class stack {
public:
	stack() : m_count(0), m_data{ 0 } {}

	// --- member functions ---
	const size_t& push(const T& value) {
		m_data[m_count] = value;
		m_count++;
		return m_count;
	}

	T pop() {
		m_count--;
		T temp = m_data[m_count];
		m_data[m_count] = 0;

		return temp;
	}

	T& peek() {
		return m_data[m_count - 1];
	}
	
	// --- capacity ---
	const size_t capacity() const {
		return N;
	}

	const size_t& size() const {
		return m_count;
	}

	const bool empty() const {
		return m_count == 0;
	}

private:
	size_t m_count;
	T m_data[N];
};

_CUSTOM_END_

template <typename T, size_t N>
bool operator==(const custom::stack<T, N>& lhs, const custom::stack<T, N>& rhs) {
	if (lhs.m_count == rhs.m_count) {
		size_t return_flag = 0;
		for (size_t i = 0; i < lhs.m_count; i++) {
			lhs.m_data[i] == rhs.m_data[i] ? NULL : ++return_flag;
		}
		return return_flag ? false : true;
	}
	return false;
}