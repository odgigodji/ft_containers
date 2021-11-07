//
// Created by Nelson Amerei on 10/31/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP
#include "ft.hpp"

namespace ft
{
template < class Key, class T, class Compare, class Allocator >
	class map {
		/*******************************************************************************
		*=================================MEMBER_TYPES=================================*
		********************************************************************************
		*___________________________________Typedefs__________________________________*
		*******************************************************************************/
	public:
		typedef Key						key_type;
		typedef T							mapped_type;
		typedef Compare					key_compare;
		typedef Allocator					allocator_type;
		typedef ft::pair<const Key, T>	value_type;
//		typedef value_type* 				pointer;
//		typedef value_type&					reference;
//		typedef const value_type*			const_pointer;
//		typedef const value_type&			const_reference;
//		typedef ptrdiff_t					difference_type;

	};
}

#endif //FT_CONTAINERS_MAP_HPP
