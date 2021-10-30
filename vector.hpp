//
// Created by Nelson Amerei on 10/24/21.
//

//#include <iostream>
//#include "iterators.hpp"

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include <iostream>
//#include "iterators.hpp"
#include "ft.hpp"

namespace ft
{
//---------------------------------ft-----------------------------------------//
template<class Tp,  class Alloc = std::allocator<Tp> >
	class vector
	{
/*******************************************************************************
*=================================MEMBER_TYPES=================================*
********************************************************************************
*___________________________________Typedefs__________________________________*
*******************************************************************************/
	public:
		typedef Tp					value_type;
		typedef Alloc				allocator_type;
//		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
//		typedef const value_type*	const_pointer;

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
*_______________________________Iterators_classes______________________________*
*******************************************************************************/
        class				iterator {
        private:
            pointer 		        _ptr;

        public:
            iterator() : _ptr(nullptr) {}
            explicit iterator(pointer ptr) : _ptr(ptr) {}
            iterator(const iterator &orig) { _ptr = orig._ptr; }
            iterator& operator = (const iterator &rhs) {
                if (_ptr != rhs._ptr) { _ptr = rhs._ptr; }
                return *this;
            }

            iterator&	operator++() { ++_ptr; return *this; }
            iterator&	operator--() { --_ptr; return *this; }
            iterator 	operator ++ (int) { return iterator(_ptr++); }
            iterator 	operator -- (int) { return iterator(_ptr--); }
            iterator&	operator += (const difference_type &n) { _ptr += n; return *this; }
            iterator&	operator -= (const difference_type &n) { _ptr -= n; return *this; }
            iterator 	operator + (const difference_type &n) const { return iterator(_ptr + n); }
            iterator 	operator - (const difference_type &n) const { return iterator(_ptr - n); }
            reference	operator * () { return *_ptr; };
			pointer		getPtr() const { return _ptr; };
            difference_type operator - (iterator const &other) const { return _ptr - other._ptr; }
//			difference_type operator + (iterator const &other) const { return _ptr + other._ptr; }
			reference       operator [] (const_reference n) const {
            	return _ptr[n];
            }
//            pointer         operator -> () { return _ptr; }
            bool		operator == (iterator const &other) const { return _ptr == other._ptr; }
            bool		operator != (iterator const &other) const { return _ptr != other._ptr; }
            bool		operator > (iterator const &other) const{ return _ptr > other._ptr; }
            bool		operator < (iterator const &other) const{ return _ptr < other._ptr; }
            bool		operator >= (iterator const &other) const { return _ptr >= other._ptr; }
            bool		operator <= (iterator const &other) const { return _ptr <= other._ptr; }
        };
//		friend    iterator  operator + (const difference_type &n, const iterator &it) { return it + n; }

        class				 reverse_iterator {
        private:
            pointer 		        _ptr;

        public:
            reverse_iterator() : _ptr(nullptr) {}
            explicit reverse_iterator(pointer ptr) : _ptr(ptr) {}
            reverse_iterator(const reverse_iterator &orig) { _ptr = orig._ptr; }
            reverse_iterator& operator = (const reverse_iterator &rhs) {
                if (_ptr != rhs._ptr) { _ptr = rhs._ptr; }
                return *this;
            }
//            const_pointer *getPtr() const { return _ptr; };
            reference   operator * () { return *_ptr; }

            reverse_iterator&	operator ++ () { --_ptr; return *this; }
            reverse_iterator&	operator -- () { ++_ptr; return *this; }
            reverse_iterator 	operator ++ (int) { return reverse_iterator(_ptr--); }
            reverse_iterator 	operator -- (int) { return reverse_iterator(_ptr++); }
            reverse_iterator&	operator += (difference_type n) { _ptr -= n; return *this; }
            reverse_iterator&	operator -= (difference_type n) { _ptr += n; return *this; }
            reverse_iterator 	operator + (difference_type n) const { return reverse_iterator(_ptr - n); }
            reverse_iterator 	operator - (difference_type n) const { return reverse_iterator(_ptr + n); }
            reference        	operator * () const { return *_ptr; };
//            difference_type	    operator - (reverse_iterator const &other) const { return other._ptr - _ptr; }
            reference        	operator [] (const_reference n) const { return _ptr[n]; }
//            pointer        	    operator -> () { return _ptr; }
            bool             	operator == (reverse_iterator const &other) const { return _ptr == other._ptr; }
            bool             	operator != (reverse_iterator const &other) const { return _ptr != other._ptr; }
            bool             	operator > (reverse_iterator const &other) const{ return _ptr > other._ptr; }
            bool             	operator < (reverse_iterator const &other) const{ return _ptr < other._ptr; }
            bool             	operator >= (reverse_iterator const &other) const { return _ptr >= other._ptr; }
            bool             	operator <= (reverse_iterator const &other) const { return _ptr <= other._ptr; }
        };


/*******************************************************************************
*===============================MEMBER_FUNCTIONS===============================*
********************************************************************************
*__________________________Constructors_and_destructor_________________________*
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
	vector(size_t n, const_reference value) :	_size(n), _capacity(n)
	{
		_arr = _alloc.allocate(n);
		for(size_t i = 0; i < n; i++) {
			_alloc.construct(_arr + i, value);
//			std::cout << "test: " << i << " " << _arr[i] << std::endl;
		}
	}

//  3)Range constructor.Constructs a container with as many elements as the range
// (first,last),with each element constructed from its corresponding
// element in that range, in the same order.
//	vector(iterator first, iterator last) : _size(0) {
//		size_t range = last - first;
//		if (range < 0) { throw std::out_of_range("vector"); }
//		_arr = _alloc.allocate(range);
//		_capacity = range;
		//insert(begin(), first, last)
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
    ~vector() {
		clear();
		_alloc.deallocate(_arr, _capacity);
	}

	//assignation operator overload

/*******************************************************************************
*_______________________________MEMBER_FUNCTIONS_______________________________*
*__________________________________Iterators___________________________________*
*******************************************************************************/
    iterator    		begin() const { return iterator(_arr); }
    iterator    		end() const { return iterator(_arr + _size); }
    reverse_iterator	rbegin() const { return reverse_iterator(_arr + _size - 1); }
    reverse_iterator	rend() const { return reverse_iterator(_arr - 1); }

/*******************************************************************************
*_________________________________Capacity:____________________________________*
*******************************************************************************/
	size_t 	size() const { return _size; }
	size_t 	max_size() const { return _alloc.max_size(); }
	void	resize(size_t n) {
		if (n > _capacity) { reserve(_capacity * 2); }
		_size = n;
	}
	size_t	capacity() const { return _capacity; }
	bool	empty() const { return !_size; }
	/*Requests that the vector capacity be at least enough to contain n elements.
	If n is greater than the current vector capacity,
	the function causes the container to reallocate its storage increasing its
	capacity to n (or greater).*/
	void	reserve (const size_t n) {
		if (n > _capacity) {
			pointer tmp = _alloc.allocate(n);
			for(size_t i = 0; i < _size; ++i) {
				_alloc.construct(tmp + i, _arr[i]);
				_alloc.destroy(_arr + i);
			}
			if (_arr) { _alloc.deallocate(_arr, _capacity); }
			_arr = tmp;
			_capacity = n;
		}
	}

/*******************************************************************************
*______________________________Element_access__________________________________*
*******************************************************************************/
		reference	operator[] (size_t n) { //fixme
			return _arr[n];
		}
		reference	at(const size_t &n) {
			if (n < _size) { return _arr[n]; }
			throw std::out_of_range("vector");
		}
		reference	front() { return _arr[0]; }
		reference 	back() { return _arr[_size - 1]; }

/*******************************************************************************
*__________________________________Modifiers___________________________________*
*******************************************************************************/
	void	assign (size_t n, const_reference value) {
		clear();
//		_alloc.deallocate(_arr, )
		if (n > _capacity) { reserve(n); }
		for(int i = 0; i < n; ++i) {
			_alloc.construct(_arr + i, value);
		}
		_size = n;
	}

	void assign (iterator first, iterator last) { //fixme
		clear();
		size_t n = last - first;
		if ( n > _capacity) { reserve(n); }
		for(; first < last; ++first) { push_back(*first); }
	}

	void	push_back(const_reference value) {
		if (_size == _capacity)
			reserve(_size ? _size * 2 : 1);
		_alloc.construct(_arr + _size, value);
		++_size;
	}

	void	pop_back() {
		if (_arr) {
			--_size;
			_alloc.destroy(_arr + _size);
		}
	}
	//insert
	iterator	erase(iterator pos) {
		_alloc.destroy(pos.getPtr());
		size_t len = sizeof(value_type) * (end().getPtr() - pos.getPtr());
		std::memmove(pos.getPtr(), pos.getPtr() + 1, len);
		--_size;
		return pos;
	}
	iterator	erase(iterator first, iterator last)
	{
		for (iterator it = first; it != last; ++it)
			_alloc.destroy(it.getPtr());
		size_t len = sizeof(value_type) * (end().getPtr() - last.getPtr());
		std::memmove(first.getPtr(), last.getPtr(), len);
		_size -= last.getPtr() - first.getPtr();
		return last;
	}

	void		swap(vector &other) {
		if (this != &other) {
			allocator_type    tmpAlloc = _alloc;
			pointer           tmpArr = _arr;
			size_t            tmpSize = _size;
			size_t            tmpCapacity = _capacity;

			_alloc = other._alloc;
			_arr = other._arr;
			_size  = other._size;
			_capacity  = other._capacity;

			other._alloc = tmpAlloc;
			other._arr = tmpArr;
			other._size = tmpSize;
			other._capacity = tmpCapacity;
		}
	}
// Removes all elements from the vector, leaving the container with a size of 0.
	void clear() {
		for(int i = 0; i < _size; ++i)
			_alloc.destroy(_arr + i);
		_size = 0;
	}

/*******************************************************************************
*__________________________________Allocator___________________________________*
*******************************************************************************/
    allocator_type get_allocator() const { return _alloc; }
};

/*******************************************************************************
*_________________________Non-member function overloads________________________*
*******************************************************************************/
    //relational operators
template<class Tp, class Alloc = std::allocator<Tp> >
bool    operator == (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
	if (lhs.size() == rhs.size())
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	return false;
}

template<class Tp, class Alloc>
bool    operator != (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
	return !(lhs == rhs);
}

template<class Tp, class Alloc>
bool    operator < (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Tp, class Alloc>
bool    operator > (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<class Tp, class Alloc>
bool    operator <= (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	if (lhs == rhs) { return true; }
	return (lhs < rhs);
}

template<class Tp, class Alloc>
bool    operator >= (const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	if (lhs == rhs) { return true; }
	return (lhs > rhs);
}
    //swap
//	};
//-----------------------------------ft---------------------------------------//
}

#endif //FT_VECTOR_HPP
