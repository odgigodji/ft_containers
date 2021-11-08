//
// Created by Nelson Amerei on 10/24/21.
//

//#include <iostream>
//#include "iterators.hpp"

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include "ft.hpp"

namespace ft
{
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
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;

		/*******************************************************************************
		*___________________________________Variables__________________________________*
		*******************************************************************************/
	private:
		allocator_type    			_alloc;
		pointer           			_arr;
		size_t            			_size;
		size_t            			_capacity;

		/*******************************************************************************
		*_______________________________Iterators_classes______________________________*
		*******************************************************************************/
	public:
		class	iterator : public ft::iterator_traits<std::random_access_iterator_tag,
				value_type> {
		private:
			pointer 		        _ptr;

		public:
			iterator() : _ptr(nullptr) {}
			explicit iterator(pointer ptr) : _ptr(ptr) {}
			iterator(const iterator &orig) { _ptr = orig._ptr; }
			iterator& operator=(const iterator &rhs) {
				if (_ptr != rhs._ptr) { _ptr = rhs._ptr; }
				return *this;
			}

			pointer		getPtr() const { return _ptr; };
			iterator&	operator++() { ++_ptr; return *this; }
			iterator&	operator--() { --_ptr; return *this; }
			iterator 	operator++(int) { return iterator(_ptr++); }
			iterator 	operator--(int) { return iterator(_ptr--); }
			iterator&	operator+=(const difference_type &n) { _ptr += n; return *this; }
			iterator&	operator-=(const difference_type &n) { _ptr -= n; return *this; }
			iterator 	operator+(const difference_type &n) const { return iterator(_ptr + n); }
			iterator 	operator-(const difference_type &n) const { return iterator(_ptr - n); }
			reference	operator*() { return *_ptr; };
			pointer		operator->() { return _ptr; }
			difference_type operator-(iterator const &orig) const { return _ptr - orig._ptr; }
			difference_type operator+(iterator const &orig) const { return _ptr + orig._ptr; }
			reference       operator[](const_reference n) const {
				return _ptr[n];
			}
			bool operator==(iterator const &orig) const { return _ptr == orig._ptr; }
			bool operator!=(iterator const &orig) const { return _ptr != orig._ptr; }
			bool operator>(iterator const &orig) const{ return _ptr > orig._ptr; }
			bool operator<(iterator const &orig) const{ return _ptr < orig._ptr; }
			bool operator>=(iterator const &orig) const { return _ptr >= orig._ptr; }
			bool operator<=(iterator const &orig) const { return _ptr <= orig._ptr; }
		};

	class	 reverse_iterator : public ft::reverse_iterator<iterator> {
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

			pointer				*getPtr() const { return _ptr; };
			reverse_iterator&	operator++() { --_ptr; return *this; }
			reverse_iterator&	operator--() { ++_ptr; return *this; }
			reverse_iterator 	operator++(int) { return reverse_iterator(_ptr--); }
			reverse_iterator 	operator--(int) { return reverse_iterator(_ptr++); }
			reverse_iterator&	operator+=(difference_type n) { _ptr -= n; return *this; }
			reverse_iterator&	operator-=(difference_type n) { _ptr += n; return *this; }
			reverse_iterator 	operator+(difference_type n) const { return reverse_iterator(_ptr - n); }
			reverse_iterator 	operator-(difference_type n) const { return reverse_iterator(_ptr + n); }
			reference        	operator*() const { return *_ptr; };
			difference_type	    operator-(reverse_iterator const &orig) const { return orig._ptr - _ptr; }
			reference        	operator[](const_reference n) const { return _ptr[n]; }
			pointer        	    operator->() { return _ptr; }
			bool	operator==(reverse_iterator const &orig) const { return _ptr == orig._ptr; }
			bool	operator!=(reverse_iterator const &orig) const { return _ptr != orig._ptr; }
			bool	operator>(reverse_iterator const &orig) const{ return _ptr > orig._ptr; }
			bool	operator<(reverse_iterator const &orig) const{ return _ptr < orig._ptr; }
			bool	operator>=(reverse_iterator const &orig) const { return _ptr >= orig._ptr; }
			bool	operator<=(reverse_iterator const &orig) const { return _ptr <= orig._ptr; }
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
			orig	-	anorig container to be used as source to initialize
			the elements of the container with.
		 */

		//1)Default constructor. Constructs an empty container, with no elements.
	public:
		vector() : _arr(nullptr), _size(0), _capacity(0) {}

		//2)Fill constructor.Constructs a container with n elements. Each element is a copy of val.
		vector(size_t n, const_reference value) :	_size(n), _capacity(n) {
			if (n > 0) {
				_arr = _alloc.allocate(_capacity);
				for(size_t i = 0; i < _capacity; i++) { _alloc.construct(_arr + i, value); }
			}
		}

		//3)Range constructor.Constructs a container with as many elements as the range
		// (first,last),with each element constructed from its corresponding
		// element in that range, in the same order.
		template <class InputIterator>
			vector(InputIterator first, InputIterator last,
			   typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>
			   ::type * = nullptr) : _size(0) {
					size_t range = last - first;
					if (range < 0) { throw std::out_of_range("vector"); }
					_arr = _alloc.allocate(range);
					_capacity = range;
					insert(begin(), first, last);
			}

		//4)Copy constructor.Constructs a container with a copy of each of the
		// elements in x, in the same order.
		vector(const vector& orig) {
			_size = orig.size();
			_capacity = orig.capacity();
			_alloc = orig.get_allocator();
	        _arr = _alloc.allocate(_capacity);
			for(size_t i = 0; i < _size; i++) { _alloc.construct(_arr + i, orig._arr[i]); }
		}

		//1)Destructor.
		~vector() {
			if(_arr) { clear(); _alloc.deallocate(_arr, _capacity); }
		}

		//Assignation operator overload.
		vector& operator=(const vector& x) {
			if (this != &x) {
				if (_arr) { clear(); _alloc.deallocate(_arr, _capacity); }
				_alloc = x.get_allocator();
				_capacity = x.capacity();
				_size = x.size();
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; ++i) { _alloc.construct(_arr + i, x._arr[i]); }
			}
			return *this;
		}
		/*******************************************************************************
		*__________________________________Iterators___________________________________*
		*******************************************************************************/
		iterator		begin() const { return iterator(_arr); }
		iterator		end() const { return iterator(_arr + _size); }
		reverse_iterator	rbegin() const { return reverse_iterator(_arr + _size - 1); }
		reverse_iterator	rend() const { return reverse_iterator(_arr - 1); }

		/*******************************************************************************
		*_________________________________Capacity:____________________________________*
		*******************************************************************************/
		size_t 	size() const { return _size; }

		size_t 	max_size() const { return _alloc.max_size(); }

		void	resize(size_t n) {
			if (n > _capacity) {
				_alloc.allocate(n);
				_capacity = n;
			}
			_size = n;
		}

		void	resize(const size_t &n, const_reference value)
		{
			if (n > _capacity)
				reserve(_capacity * 2);
			for (size_t i = _size; i < n; ++i)
				_alloc.construct(_arr + i, value);
			_size = n;
		}

		size_t	capacity() const { return _capacity; }

		bool	empty() const { return !_size; }

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
		reference	operator[] (const size_t n) { return _arr[n]; }

		reference	at(const size_t &n) {
			if (n < _size) { return _arr[n]; }
			throw std::out_of_range("vector");
		}

		reference	front() { return _arr[0]; }

		reference 	back() { return _arr[_size - 1]; }

		pointer		data() { return _arr; };

		/*******************************************************************************
		*__________________________________Modifiers___________________________________*
		*******************************************************************************/
		template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			assign (InputIterator first, InputIterator last) {
				clear();
				size_t len = last - first;
				if (len > _capacity) { reserve(len); }
				for(; first != last; ++first) {
					push_back(*first);
				}
			}

		void		assign (size_t n, const_reference value) {
			clear();
			if (n > _capacity) { reserve(n); }
			for(size_t i = 0; i < n; ++i) { _alloc.construct(_arr + i, value); }
			_size = n;
		}

		void		push_back(const_reference value) {
			if (_size == _capacity) {
				if (!_size) { reserve(1); }
				else { reserve(_size * 2); }
			}
			_alloc.construct(_arr + _size, value);
			++_size;
		}

		void		pop_back() {
			if (_arr) {
				--_size;
				_alloc.destroy(_arr + _size);
			}
		}

		iterator	insert(iterator position, const_reference val) {
			if (_size == _capacity) {
				size_t    i = (position.getPtr() - begin().getPtr());
				reserve(_size * 2);
				position = begin() + i;
			}
			size_t len = sizeof(value_type) * (end().getPtr() - position.getPtr());
			std::memmove(position.getPtr() + 1, position.getPtr(), len);
			_alloc.construct(position.getPtr(), val);
			++_size;
			return position;
		}


		void		insert(iterator position, const size_t &count, const_reference val) {
			if (_size + count > _capacity) {
				size_t    id = (position.getPtr() - begin().getPtr());
				if (_size + count > _capacity * 2) { reserve(_arr + count); }
				else { reserve(_capacity * 2); }
				position = begin() + id;
			}
			size_t len = sizeof(val) * (end().getPtr() - position.getPtr());
			std::memmove(position.getPtr() + count, position.getPtr(), len);
			for (size_t i = 0; i != count; ++i)
				_alloc.construct((position + i).getPtr(), val);
			_size += count;
		}

		template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			insert(iterator pos, InputIterator first, InputIterator last) {
				size_t    id = last - first;
				if (_size + id > _capacity) {
					size_t    i = (pos.getPtr() - begin().getPtr());
					if (_size + id > _capacity * 2) { reserve(_size + id); }
					else { reserve(_capacity * 2); }
					pos = begin() + i;
				}
				size_t len = sizeof(value_type) * (end().getPtr() - pos.getPtr());
				std::memmove(pos.getPtr() + id, pos.getPtr(), len);
				for (size_t i = 0; i != id; ++i)
					_alloc.construct((pos + i).getPtr(), *(first + i));
				_size += id;
			}

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

		void		swap(vector &orig) {
			if (this != &orig ) {
				allocator_type    tmp_alloc = _alloc;
				pointer           tmp_arr = _arr;
				size_t            tmp_size = _size;
				size_t            tmp_capacity = _capacity;

				_alloc = orig.get_allocator();
				_arr = orig._arr;
				_size  = orig._size;
				_capacity  = orig._capacity;

				orig._alloc = tmp_alloc;
				orig._arr = tmp_arr;
				orig._size = tmp_size;
				orig._capacity = tmp_capacity;
			}
		}
		// Removes all elements from the vector, leaving the container with a size of 0.
		void		clear() {
			if(_capacity > 0) {
				for(size_t i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				_size = 0;
			}
		}

		/*******************************************************************************
		*__________________________________Allocator___________________________________*
		*******************************************************************************/
    	allocator_type get_allocator() const { return _alloc; }
};
/*******************************************************************************
*_________________________Non-member function overloads________________________*
*******************************************************************************/

template<class Tp, class Alloc>
	bool    operator==(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

template<class Tp, class Alloc >
	bool    operator!=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		return !(lhs == rhs);
	}

template<class Tp, class Alloc>
	bool    operator<(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

template<class Tp, class Alloc>
	bool    operator>(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

template<class Tp, class Alloc>
	bool    operator<=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		if (lhs == rhs) { return true; }
		return (lhs < rhs);
	}

template<class Tp, class Alloc>
	bool    operator>=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs) {
		if (lhs == rhs) { return true; }
		return (lhs > rhs);
	}

template <class T, class Alloc>
	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
}

#endif //FT_VECTOR_HPP
