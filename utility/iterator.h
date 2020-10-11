#pragma once
#include "..\core\custom_def.h"

// custom containers library - iterator interface

_CUSTOM_BEGIN_

template <typename T, typename iterator_type>
class base_iterator {
public:
	using T_ptr = T*;
	using T_ref = T&;

public:

	virtual T_ref operator*() = 0;
	virtual T_ptr operator->() = 0;

	virtual iterator_type& operator++() = 0;
	virtual iterator_type operator++(int) = 0;

	virtual iterator_type& operator--() = 0;
	virtual iterator_type operator--(int) = 0;

	virtual bool operator==(iterator_type&) = 0;
	virtual bool operator!=(iterator_type&) = 0;
	//virtual T_ref operator[](const size_t) = 0;
};

template <typename T, typename iterator_type>
class base_forward_iterator {
public:
	using T_ptr = T*;
	using T_ref = T&;

	virtual T_ref operator*() = 0;
	virtual T_ptr operator->() = 0;

	virtual iterator_type& operator++() = 0;
	virtual iterator_type operator++(int) = 0;
};

_CUSTOM_END_