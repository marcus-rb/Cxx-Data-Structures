#pragma once

#include "..\core\custom_def.h"

_CUSTOM_BEGIN_

template <typename T>
size_t max(const T& left, const T& right) {
	return left < right ? right : left;
}

_CUSTOM_END_ 