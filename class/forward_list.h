#pragma once

// CLASS SETUP
/* [ ] constructor
 * [ ] destructor
 * [ ] operator=
 * [ ] assign
 * 
 */

#include "..\core\custom_def.h"
#include "..\utility\iterator.h"
#include "..\utility\memory.h"

_CUSTOM_BEGIN_

template <typename flist_type>
class forward_list_iterator : public base_forward_iterator<typename flist_type::value_type, forward_list_iterator<flist_type> {
public:
	using T_ptr = typename flist_type::T_ptr;
	using T_ref = typename flist_type::T_ref;

	using value_type = typename flist_type::value_type;
};

template <typename T, typename alloc = allocator<T>>
class forward_list {
public:
	using iterator = forward_list_iterator<forward_list<T, alloc>>;

	using T_ptr = T*;
	using T_ref = T&;

	using const_T_ptr = const T*;
	using const_T_ref = const T&;

	using value_type = T;
private:
	class list_node;

	list_node* m_head;
	list_node* m_tail;
public:

	forward_list() : m_head(nullptr), m_tail(nullptr) noexcept;

	// --- ELEMENT ACCESS ---

	// --- ITERATORS ---

	// --- MODIFIERS ---

private:
	class list_node {
		T_ptr m_list_data;
		list_node* m_next;
	};
};

_CUSTOM_END_

template <typename T, typename alloc = custom::allocator<T>>
bool operator==(custom::forward_list<T, alloc>& lhs, custom::forward_list<T, alloc>& rhs) {

}