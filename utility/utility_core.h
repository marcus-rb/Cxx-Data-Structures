#pragma once

#include "..\core\custom_def.h"

_CUSTOM_BEGIN_

template <typename T>
size_t max(const T& left, const T& right) {
	return left < right ? right : left;
}

template <typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

#if false
template<typename T>
void swap<custom::vector<T>>(custom::vector<T>& a, custom::vector<T>& b);

template<typename T, size_t N>
void swap<custom::array<T, N>>(custom::array<T, N>& a, custom::array<T, N>& b);
#endif

_CUSTOM_END_ 