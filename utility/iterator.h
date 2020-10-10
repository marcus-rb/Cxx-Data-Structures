#pragma once
#include "..\core\custom_def.h"

// custom containers library - iterator interface

_CUSTOM_BEGIN_

template <typename T>
class base_iterator {
public:
	using T_ptr = T*;
	using T_ref = T&;

public:

	virtual T_ref operator*() = 0;
	virtual T_ptr operator->() = 0;

	virtual base_iterator& operator++() = 0;
	virtual base_iterator operator++(int) = 0;

	virtual base_iterator& operator--() = 0;
	virtual base_iterator operator--(int) = 0;

	virtual bool operator==(base_iterator&) = 0;
	virtual bool operator!=(base_iterator&) = 0;
	//virtual T_ref operator[](const size_t) = 0;
};

template <typename T>
class base_forward_iterator {
public:
	using T_ptr = T*;
	using T_ref = T&;

	virtual T_ref operator*() = 0;
	virtual T_ptr operator->() = 0;

	virtual base_forward_iterator& operator++() = 0;
	virtual base_forward_iterator operator++(int) = 0;
};

_CUSTOM_END_