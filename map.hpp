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

		class value_compare {
		protected:
			key_compare    _cmp;

		public:
			explicit	value_compare(const key_compare &c) : _cmp(c) {}
			bool		operator ()(const_reference val1,
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
		*_______________________________Iterators_classes______________________________*
		*******************************************************************************/
		class    iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
				private:
					node*	_node;

					node*	find_min(node *p) {
						if (p == NULL) { std::cout << "The tree is empty" << std::endl; }
						else { while(p->left !=NULL) { p = p->left; } }
						return p;
					}
					node*	find_max(node *p) {
						if (p == NULL) { std::cout << "The tree is empty" << std::endl; }
						else { while(p->right !=NULL) { p = p->right; } }
						return p;
//						return p->right ? find_max(p->right) : p;
					}

				public:
					iterator() : _node(nullptr) {}
					iterator(node *ptr) : _node(ptr) {}
					~iterator() {}
					iterator(const iterator &other) { *this = other; }

					node*			getNode() const { return _node; }

					iterator&		operator = (const iterator &other) {
						if(this != other) { _node = other._node; }
						return *this;
					}
					reference	operator * () { return _node->value; }
					pointer		operator -> () { return &_node->value; }
					bool    operator == (const iterator &rhs) { return this->_node == rhs._node; }
					bool    operator != (const iterator &hrs) { return this->_node != hrs._node; }

					iterator&    operator ++ () {
						if (_node->isBegin)
							_node = _node->parent;
						else if (_node->right)
							_node = find_min(_node->right);
						else {
							node    *tmp = _node->parent;
							while (tmp && tmp->value.first < _node->value.first)
								tmp = tmp->parent;
							_node = tmp;
						}
						return *this;
					}

					iterator&        operator -- () {
						if (_node->isEnd)
							_node = _node->parent;
						else if (_node->left)
							_node = find_max(_node->left);
						else {
							node    *tmp = _node->parent;
							while (tmp && tmp->value.first > _node->value.first)
								tmp = tmp->parent;
							_node = tmp;
						}
						return *this;
					}

					iterator        operator ++ (int) {
						iterator    tmp(_node);
						operator++();
						return tmp;
					}

					iterator        operator -- (int) {
						iterator    tmp(_node);
						operator--();
						return tmp;
					}
				};

		/*******************************************************************************
		*===============================MEMBER_FUNCTIONS===============================*
		********************************************************************************
		*__________________________Constructors_and_destructor_________________________*
		*******************************************************************************/
	public:
		/*
		 * Parameters:
		alloc	-	allocator to use for all memory allocations of this container
		comp	-	comparison function object to use for all comparisons of keys
		first, last	-	the range to copy the elements from
		other	-	another container to be used as source to initialize the
		 elements of the container with.
		init	-	initializer list to initialize the elements of the container with.
		 */

		/* 						Constructs an empty container.					  */
		map() : _size(0) {
			_alloc.allocate(sizeof(node));
			_alloc.construct(_tree, node());
			_beginNode = _endNode = _tree;
		}

		/* Constructs the container with the contents of the range [first, last). */
		template< class InputIt > map( InputIt first, InputIt last, //fixme
					 const Compare& comp = Compare(),
					 const Allocator& alloc = Allocator() ) {
			;
		}

		/*******************************************************************************
		*__________________________________Iterators___________________________________*
		*******************************************************************************/
		//	begin
		//	end
		//	rbegin
		//	rend

		/*******************************************************************************
		*_________________________________Capacity:____________________________________*
		*******************************************************************************/
		//	empty
		//	size
		//	max_size

		/*******************************************************************************
		*______________________________Element_access__________________________________*
		*******************************************************************************/
		//	operator[]

		/*******************************************************************************
		*__________________________________Modifiers___________________________________*
		*******************************************************************************/
		//insert
		//		ft::pair<iterator,bool> insert (const value_type& val);
		//		iterator insert (iterator position, const value_type& val);
		//template <class InputIterator>
		//		void insert (InputIterator first, InputIterator last);

		//erase
		//swap
		//clear

		/*******************************************************************************
		*__________________________________Observers___________________________________*
		*******************************************************************************/
		//key_comp
		//value_comp

		/*******************************************************************************
		*__________________________________Operations___________________________________*
		*******************************************************************************/
		//find
		//count
		//lower_bound
		//upper_bound
		//equal_range

		/*******************************************************************************
		*__________________________________Allocator___________________________________*
		*******************************************************************************/
		//get_allocator
	};
	//==
}

#endif //FT_CONTAINERS_MAP_HPP
