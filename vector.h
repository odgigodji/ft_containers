//
// Created by Nelson Amerei on 10/24/21.
//



#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

namespace ft {
//---------------------------------ft-----------------------------------------//

	template<class T, class Allocator>
	class vector
	{
	public:
	/***********************************************************************
	*----------------------------MEMBER TYPES----------------------------*
	***********************************************************************/

		typedef T                    value_type;
		typedef Allocator            allocator_type;
		size_t						 size_type;
		typedef ptrdiff_t            difference_type;

		typedef value_type&          reference;
		typedef const value_type&    const_reference;
		typedef value_type*          pointer;
		typedef const value_type*    const_pointer;

		//iterators
		class						iterator;
		class						const_iterator;
		class						reverse_iterator;
		class						const_reverse_iterator;

//	private:
		/* VARIABLES    */
//		allocator_type    _alloc;
//		pointer            _arr;
//		size_t            _arrSize;
//		size_t            _arrCap;

//	public:
		/*    ITERATORS    */


	};


//-----------------------------------ft---------------------------------------//
}

#endif //FT_CONTAINERS_VECTOR_H
