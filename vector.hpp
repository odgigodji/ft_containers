//
// Created by Nelson Amerei on 10/24/21.
//

//#include <iostream>
//#include "iterators.hpp"

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include <iostream>
//#include "iterators.hpp"

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
        class						iterator {
        private:
            pointer 		        _ptr;

        public:
            iterator() : _ptr(nullptr) {}
            explicit iterator(pointer ptr) : _ptr(ptr) {}
            iterator(const iterator &other) { *this = other; }

            reference   operator * () { return *_ptr; };
        };
//		class						 iterator;
//		class						 const_iterator;
//		class						 reverse_iterator;
//		class						 const_reverse_iterator;

/*******************************************************************************
*___________________________________Variables__________________________________*
*******************************************************************************/
//	private:
	public:
		allocator_type    			_alloc;
		pointer           			_arr;
		size_t            			_size;
		size_t            			_capacity;


/*******************************************************************************
*===============================MEMBER FUNCTIONS===============================*
********************************************************************************
*__________________________Constructors and destructor_________________________*
*******************************************************************************/

/*
	Parameters:
	alloc	-	allocator to use for all memory allocations of this container
	value	-	the value to initialize elements of the container with
	first, last	-	the range to copy the elements from
	other	-	another container to be used as source to initialize
 	the elements of the container with.
	init	-	initializer list to initialize the elements of the container with
 */

//	1)Default constructor. Constructs an empty container, with no elements.
public:
	vector() : _arr(nullptr), _size(0), _capacity(0) {}

//	2)Fill constructor.Constructs a container with n elements. Each element is a copy of val.
	vector(size_type n, const_reference value) :	_size(n), _capacity(n)
	{
		_arr = _alloc.allocate(n);
		for(size_t i = 0; i < n; i++) {
			_alloc.construct(_arr + i, value);
			std::cout << "test: " << i << " " << _arr[i] << std::endl;
		}
	}

//  3)Range constructor.Constructs a container with as many elements as the range
// (first,last),with each element constructed from its corresponding
// element in that range, in the same order.
//	template<class Iter = iterator>
//	vector(iterator first, iterator last) : _size(0) {
//		size_t range = last - first;
//		if (range < 0) { throw std::out_of_range("vector"); }
//		_arr = _alloc.allocate(range);
//		_capacity = range;
//		//insert(begin(), first, last)
//	}

//  4)Copy constructor.Constructs a container with a copy of each of the
// elements in x, in the same order.
	vector(const vector& other) {
		_size = other.size();
        _capacity = other.capacity();
//        _alloc = other.get_allocator();
        _arr = _alloc.allocate(_capacity);
		for(size_t i = 0; i < _size; i++) {
			_alloc.construct(_arr + i, other._arr[i]);
		}
	}

//  1)Destructor.
//    ~vector() {
////	    _clear
//	    _arr = nullptr;
//	}

	//assignation operator overload

/*******************************************************************************
*____________________________________Getters___________________________________*
*******************************************************************************/
	allocator_type get_allocator() const { return _alloc; }
	size_type size() const { return _size; }
	size_type capacity() const { return _capacity; }

/*******************************************************************************
*_______________________________Member_functions_______________________________*
*******************************************************************************/
    iterator    begin()  { return iterator(_arr); }
    iterator    end() {
//        std::cout << "end: size=" << _size << " _arr + _size =" << *(_arr + _size - 1 ) << std::endl;
        return iterator(_arr + _size - 1);
    }

	};
//-----------------------------------ft---------------------------------------//
}

#endif //FT_VECTOR_HPP
