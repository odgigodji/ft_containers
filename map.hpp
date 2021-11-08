//
// Created by Nelson Amerei on 10/31/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP
#include "ft.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
	        class Allocator = std::allocator<T> >
	class map {
		/*******************************************************************************
		*=================================MEMBER_TYPES=================================*
		********************************************************************************
		*___________________________________Typedefs__________________________________*
		*******************************************************************************/
	public:
		typedef Key								key_type;
		typedef T								mapped_type;
		typedef Compare							key_compare;
		typedef Allocator						allocator_type;
		typedef ft::pair<const Key, T>			value_type;
		typedef value_type* 					pointer;
		typedef value_type&						reference;
		typedef const value_type*				const_pointer;
		typedef const value_type&				const_reference;
		typedef ptrdiff_t						difference_type;

		/*******************************************************************************
		*__________________________________Node of tree________________________________*
		*******************************************************************************/
	private:
		struct	node {
			value_type	value; 			/*    пара ключ - значение            */
			size_t		height;			/*    высота поддерева                */
			node*		parent;		/*    указатель на родителя           */
			node*		right;			/*    указатель на правое поддерево   */
			node*		left; 			/*    указатель на левое поддерево    */
			bool		isBegin;		/*    true - узел перед минимальным	  */
			bool		isEnd;			/*    true - узел после максимального */

			/*   					NEW NODE CONSTRUCTORS :					  */
			node() :							height(0),
												parent(nullptr),
												right(nullptr),
												left(nullptr),
												isBegin(true),
												isEnd(true) {}

			explicit node(const_reference val):	value(ft::make_pair(val.first, val.second)),
												height(1),
												parent(nullptr),
												right(nullptr),
												left(nullptr),
												isBegin(false),
												isEnd(false) {}
		};

		class compare_value {
				public:
					key_compare    _cmp;

					explicit	compare_value(const key_compare &c) : _cmp(c) {}

					bool	operator ()(const_reference val1,
							const_reference val2) const { return _cmp(val1.first, val2.first); }
		};
		/*******************************************************************************
		*____________________________________Variables_________________________________*
		*******************************************************************************/
		node*									_tree;
		size_t          						_size;
		allocator_type							_alloc;
		node*									_beginNode;
		node*									_endNode;
		key_compare								_cmp;

		/*******************************************************************************
		*===============================MEMBER_FUNCTIONS===============================*
		********************************************************************************
		*__________________________Constructors_and_destructor_________________________*
		*******************************************************************************/

		map() : _tree(new node()), _size(0) { _beginNode = _endNode = _tree; }
	};
}

#endif //FT_CONTAINERS_MAP_HPP
