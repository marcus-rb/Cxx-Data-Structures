#pragma once

#include "..\core\custom_def.h"

_CUSTOM_BEGIN_

template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
	typedef T type;
};

template <typename T>
bool is_object() {
	return true;
}

_CUSTOM_END_