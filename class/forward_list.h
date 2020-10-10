#pragma once

#include "..\core\custom_def.h"
#include "..\utility\iterator.h"
#include "..\utility\memory.h"

_CUSTOM_BEGIN_

template <typename forward_list>
class forward_list_iterator : public base_forward_iterator<typename forward_list::T> {
public:

};

template <typename T, typename alloc_type = allocator<T>>
class forward_list {

};

_CUSTOM_END_