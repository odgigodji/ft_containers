//
// Created by Nelson Amerei on 10/24/21.
//

#include <iostream>

namespace ft
{
//---------------------------------ft-----------------------------------------//
	template<class Tp, class Alloc>
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
		class						 const_iterator;
		class						 reverse_iterator;
		class						 const_reverse_iterator;

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

	vector() : _arr(nullptr), _size(0), _capacity(0) {}

//	vector(size_type &n, const_reference value) : _arr(_alloc.allocate(n)),
//		_size(n), _capacity(n)
//	{
//		for (size_t i = 0; i < _size; ++i)
//			_alloc.construct(_arr + i, value);
//	}
//
//	vector(const size_t &count)
//	{
//		if (count < 0)
//			throw std::out_of_range("vector");
//		_arr = _alloc.allocate(count);
//		_arrCap = count;
//		assign(count, value_type());
//	}
//
//	template<class _InputIt>
//			vector( _InputIt first, _InputIt last,
//					typename ft::enable_if<std::__is_input_iterator<_InputIt>::value>::type * = nullptr )
//					{
//		size_t    range = last - first;
//		if (last - first < 0)
//			throw std::out_of_range("vector");
//		_arr = _alloc.allocate(range);
//		_arrSize = 0;
//		_arrCap = range;
//		insert(begin(), first, last);
//					}
//
//					vector(const vector &other)
//					: _alloc(other._alloc), _arrSize(other._arrSize), _arrCap(other._arrCap)
//					{
//		_arr = _alloc.allocate(_arrCap);
//		for (size_t i = 0; i < _arrSize; ++i)
//			_alloc.construct(_arr + i, other._arr[i]);
//					}

	};
//-----------------------------------ft---------------------------------------//
}

