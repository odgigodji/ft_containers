//
// Created by Nelson Amerei on 10/24/21.
//

//#include <iostream>
//#include "iterators.hpp"

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include <iostream>

namespace ft
{
//---------------------------------ft-----------------------------------------//
template<class Tp,  class Alloc = std::allocator<Tp> >
	class vector
	{
/*******************************************************************************
*=================================MEMBER TYPES=================================*
********************************************************************************
*___________________________________Typedefs__________________________________*
*******************************************************************************/
	public:
		typedef Tp					value_type;
		typedef Alloc				allocator_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

/*******************************************************************************
*___________________________________Iterators__________________________________*
*******************************************************************************/
		class						 iterator;
//		class						 const_iterator;
//		class						 reverse_iterator;
//		class						 const_reverse_iterator;

/*******************************************************************************
*___________________________________Variables__________________________________*
*******************************************************************************/
	private:
		allocator_type    			_alloc;
		pointer           			_arr;
		size_t            			_size;
		size_t            			_capacity;


/*******************************************************************************
*===============================MEMBER FUNCTIONS===============================*
********************************************************************************
*_________________________________Constructors_________________________________*
*******************************************************************************/

//	1)Default constructor. Constructs an empty container with a default-constructed allocator.
	vector() : _arr(nullptr), _size(0), _capacity(0) {}

//	2)Constructs an empty container with the given allocator alloc.
	explicit vector(const Allocator& alloc ) : _arr(nullptr),
												_size(0),
												_capacity(0),
												_alloc(alloc) {}

//	3) Constructs the container with count copies of elements with value value.
	explicit vector( size_type count, const T& value = T(),
				 const Allocator& alloc = Allocator()) {
		_ocunt = count;

	}


	};
//-----------------------------------ft---------------------------------------//
}

#endif //FT_VECTOR_HPP
