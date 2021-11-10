//
// Created by Nelson Amerei on 10/31/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP
#include "ft.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
	        class Allocator = std::allocator<ft::pair<Key, T> > >
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
			node*		parent;			/*    указатель на родителя           */
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
			node(const node &orig) { *this = orig; }

			~node() {};
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
		private:
			node*									_tree;
			size_t          						_size;
			allocator_type							_alloc;
			node*									_beginNode;
			node*									_endNode;
			key_compare								_cmp;

		/*******************************************************************************
		*_______________________________Iterators_classes______________________________*
		*******************************************************************************/
		public:
			class    iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
				private:
					node*	_node;

					node*	find_min(node *p) {
						while(p->left !=NULL) { p = p->left; }
						return p;
					}
					node*	find_max(node *p) {
						while(p->right != NULL) { p = p->right; }
						return p;
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
			_tree = _alloc.allocate(sizeof(node));
//			_tree = new(node);
//			_alloc.construct(_tree);
//			std::cout << _tree->height << std::endl;
			_beginNode = _endNode = _tree;
		}

		/* Constructs the container with the contents of the range [first, last). */
		template< class InputIt > map( InputIt first, InputIt last) { //fixme
			;
		}

		/*******************************************************************************
		*__________________________________Iterators___________________________________*
		*******************************************************************************/
		//	begin
		iterator	begin() {
			return _size ? ++iterator(_beginNode) : iterator(_beginNode);
		}
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
//		ft::pair<iterator,bool> insert (const value_type& val) {
//			_tree->right = val;
//			return(ft::make_pair(nullptr, true));
			//if elem == val - false ; return;
//			return(ft::make_pair(iteratr, ture))

//			if (val == NULL)
//			{
////				p = new node;
//				_alloc.allocate(node);
//				_tree.construct(_tree, val);
//
//				p->element = x;
//				p->left=NULL;
//				p->right = NULL;
//				p->height=0;
//				if (p==NULL)
//				{
//					cout<<"Out of Space\n"<<endl;
//				}
//			}
//			else
//			{
//				if (x<p->element)
//				{
//					insert(x,p->left);
//					if ((bsheight(p->left) - bsheight(p->right))==2)
//					{
//						if (x < p->left->element)
//						{
//							p=srl(p);
//						}
//						else
//						{
//							p = drl(p);
//						}
//					}
//				}
//				else if (x>p->element)
//				{
//					insert(x,p->right);
//					if ((bsheight(p->right) - bsheight(p->left))==2)
//					{
//						if (x > p->right->element)
//						{
//							p=srr(p);
//						}
//						else
//						{
//							p = drr(p);
//						}
//					}
//				}
//				else
//				{
//					cout<<"Element Exists\n"<<endl;
//				}
//			}
//		}


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
