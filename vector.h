//
// Created by Nelson Amerei on 10/24/21.
//



#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

namespace ft {

	template<class T, class Allocator>
	class vector
	{
	public:
	/***********************************************************************
	*----------------------------MEMBER TYPES----------------------------*
	***********************************************************************/

		typedef T                    value_type;
		typedef Allocator            allocator_type;

		typedef ptrdiff_t            difference_type;
		typedef value_type&          reference;
		typedef const value_type&    const_reference;
		typedef value_type*          pointer;
		typedef const value_type*    const_pointer;

	};



}

#endif //FT_CONTAINERS_VECTOR_H
