#pragma once

#include "ft.hpp"

namespace ft
{
	enum Compare
	{
		EQUAL,
		LESS,
		GREATER
	};

	template < class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
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

		/*							Allocator for node 							*/
		typedef typename allocator_type::template rebind<node>::other	allocator_rebind_node;

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
		allocator_rebind_node					_nodeAlloc;

		/*******************************************************************************
		*_______________________________Iterators_classes______________________________*
		*******************************************************************************/
	public:
		class iterator;

		class    iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
		private:
			node*	_node;

			node*	find_min(node *p) {
				return p->left ? find_min(p->left) : p;
			}
			node*	find_max(node *p) {
				return p->right ? find_max(p->right) : p;
			}

		public:
			iterator() : _node(nullptr) {}
			iterator(node *ptr) : _node(ptr) {}
			~iterator() {}
			iterator(const iterator &other) { *this = other; }

			node*			getNode() const { return _node; }

			iterator&		operator = (const iterator &other) {
				_node = other._node;
				return *this;
			}
			reference	operator*() { return _node->value; }
			pointer		operator->() { return &_node->value; }
			bool    operator==(const iterator &rhs) { return this->_node == rhs._node; }
			bool    operator!=(const iterator &hrs) { return this->_node != hrs._node; }

			iterator&    operator++() {
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

			iterator&        operator--() {
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

			iterator        operator++(int) {
				iterator    tmp(_node);
				operator++();
				return tmp;
			}

			iterator        operator--(int) {
				iterator    tmp(_node);
				operator--();
				return tmp;
			}
		};

	public:
/*    ITERATORS    */
//		class iterator;

		class const_iterator;

		class reverse_iterator;

		class const_reverse_iterator;


		/*    Const Iterator    */
		class const_iterator
				: public ft::iterator_traits<std::bidirectional_iterator_tag, value_type>
		{
		private:
			node *_node;

			node *find_min(node *p)
			{ return p->left ? find_min(p->left) : p; }

			node *find_max(node *p)
			{ return p->right ? find_max(p->right) : p; }

		public:
			const_iterator() : _node(nullptr)
			{}

			const_iterator(node *ptr) : _node(ptr)
			{}

			~const_iterator()
			{}

			const_iterator(const const_iterator &other)
			{ *this = other; }

			const_iterator(const iterator &other)
			{ *this = other; }

			node *getNode() const
			{ return _node; }

			const_iterator &operator=(const const_iterator &other)
			{
				_node = other._node;
				return *this;
			}

			const_iterator &operator=(const iterator &other)
			{
				_node = other.getNode();
				return *this;
			}

			bool operator==(const const_iterator &other)
			{ return this->_node == other._node; }

			bool operator!=(const const_iterator &other)
			{ return this->_node != other._node; }

			bool operator==(const iterator &other)
			{ return this->_node == other.getNode(); }

			bool operator!=(const iterator &other)
			{ return this->_node != other.getNode(); }

			const_reference operator*() const
			{ return _node->value; }

			const_pointer operator->() const
			{ return &_node->value; }

			const_iterator &operator++()
			{
				if (_node->isBegin)
					_node = _node->parent;
				else if (_node->right)
					_node = find_min(_node->right);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first < _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			const_iterator &operator--()
			{
				if (_node->isEnd)
					_node = _node->parent;
				else if (_node->left)
					_node = find_max(_node->left);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first > _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator tmp(_node);
				operator++();
				return tmp;
			}

			const_iterator operator--(int)
			{
				const_iterator tmp(_node);
				operator--();
				return tmp;
			}
		};

		/*    Reverse Iterator */
		class reverse_iterator : public ft::reverse_iterator<iterator>
		{
		private:
			node *_node;

			node *find_min(node *p)
			{ return p->left ? find_min(p->left) : p; }

			node *find_max(node *p)
			{ return p->right ? find_max(p->right) : p; }

		public:
			reverse_iterator() : _node(nullptr)
			{}

			reverse_iterator(node *ptr) : _node(ptr)
			{}

			~reverse_iterator()
			{}

			reverse_iterator(const reverse_iterator &other)
			{ *this = other; }

			node *getNode() const
			{ return _node; }

			reverse_iterator &operator=(const reverse_iterator &other)
			{
				_node = other._node;
				return *this;
			}

			bool operator==(const reverse_iterator &other)
			{ return this->_node == other._node; }

			bool operator!=(const reverse_iterator &other)
			{ return this->_node != other._node; }

			bool operator==(const const_reverse_iterator &other)
			{ return this->_node == other.getNode(); }

			bool operator!=(const const_reverse_iterator &other)
			{ return this->_node != other.getNode(); }

			reference operator*()
			{ return _node->value; }

			pointer operator->()
			{ return &_node->value; }

			reverse_iterator &operator++()
			{
				if (_node->isEnd)
					_node = _node->parent;
				else if (_node->left)
					_node = find_max(_node->left);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first > _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			reverse_iterator &operator--()
			{
				if (_node->isBegin)
					_node = _node->parent;
				else if (_node->right)
					_node = find_min(_node->right);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first < _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(_node);
				operator++();
				return tmp;;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(_node);
				operator--();
				return tmp;
			}
		};

		/*    Const Reverse Iterator    */
		class const_reverse_iterator
				: public ft::reverse_iterator<const_iterator>
		{
		private:
			node *_node;

			node *find_min(node *p)
			{ return p->left ? find_min(p->left) : p; }

			node *find_max(node *p)
			{ return p->right ? find_max(p->right) : p; }

		public:
			const_reverse_iterator() : _node(nullptr)
			{}

			const_reverse_iterator(node *ptr) : _node(ptr)
			{}

			~const_reverse_iterator()
			{}

			const_reverse_iterator(const const_reverse_iterator &other)
			{ *this = other; }

			const_reverse_iterator(const reverse_iterator &other)
			{ *this = other; }

			node *getNode() const
			{ return _node; }

			const_reverse_iterator &
			operator=(const const_reverse_iterator &other)
			{
				_node = other._node;
				return *this;
			}

			const_reverse_iterator &operator=(const reverse_iterator &other)
			{
				_node = other.getNode();
				return *this;
			}

			bool operator==(const const_reverse_iterator &other)
			{ return this->_node == other._node; }

			bool operator!=(const const_reverse_iterator &other)
			{ return this->_node != other._node; }

			bool operator==(const reverse_iterator &other)
			{ return this->_node == other.getNode(); }

			bool operator!=(const reverse_iterator &other)
			{ return this->_node != other.getNode(); }

			const_reference operator*()
			{ return _node->value; }

			const_pointer operator->()
			{ return &_node->value; }

			const_reverse_iterator &operator++()
			{
				if (_node->isEnd)
					_node = _node->parent;
				else if (_node->left)
					_node = find_max(_node->left);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first > _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			const_reverse_iterator &operator--()
			{
				if (_node->isBegin)
					_node = _node->parent;
				else if (_node->right)
					_node = find_min(_node->right);
				else
				{
					node *tmp = _node->parent;
					while (tmp && tmp->value.first < _node->value.first)
						tmp = tmp->parent;
					_node = tmp;
				}
				return *this;
			}

			const_reverse_iterator operator++(int)
			{
				const_reverse_iterator tmp(_node);
				operator++();
				return tmp;
			}

			const_reverse_iterator operator--(int)
			{
				const_reverse_iterator tmp(_node);
				operator--();
				return tmp;
			}
		};


		/*******************************************************************************
		*===============================MEMBER_FUNCTIONS===============================*
		********************************************************************************
		*__________________________Constructors_and_destructor_________________________*
		*******************************************************************************/

/*    CONSTRUCTORS    */
		map() : _tree(new node()), _size(0)
		{ _beginNode = _endNode = _tree; }

		template<class _InputIt>
		map(_InputIt first, _InputIt last) : _tree(new node()), _size(0)
		{
			_beginNode = _endNode = _tree;
			insert(first, last);
		}

		map(const map &other) : _tree(new node()), _size(0)
		{
			_beginNode = _endNode = _tree;
			*this = other;
		}

/*    DESTRUCTOR    */
		~map()
		{ delete_tree(_tree); }

/*    ASSIGNATION OPERATOR OVERLOAD    */
		map &operator=(const map &other)
		{
			if (this != &other)
			{
				clear();
				insert(other.begin(), other.end());
			}
			return *this;
		}

/*    MEMBER FUNCTIONS    */
		iterator begin()
		{ return _size ? ++iterator(_beginNode) : iterator(_beginNode); }

		iterator end()
		{ return iterator(_endNode); }

		const_iterator begin() const
		{
			return _size ? ++const_iterator(_beginNode) : const_iterator(
					_beginNode);
		}

		const_iterator end() const
		{ return const_iterator(_endNode); }

		const_iterator cbegin() const
		{
			return _size ? ++const_iterator(_beginNode) : const_iterator(
					_beginNode);
		}

		const_iterator cend() const
		{ return const_iterator(_endNode); }

		reverse_iterator rbegin()
		{ return --reverse_iterator(_endNode); }

		reverse_iterator rend()
		{ return reverse_iterator(_beginNode); }

		const_reverse_iterator rbegin() const
		{ return --const_reverse_iterator(_endNode); }

		const_reverse_iterator rend() const
		{ return const_reverse_iterator(_beginNode); }

		const_reverse_iterator crbegin() const
		{ return --const_reverse_iterator(_endNode); }

		const_reverse_iterator crend() const
		{ return const_reverse_iterator(_beginNode); }

		size_t size() const
		{ return _size; }

		size_t max_size() const
		{ return _alloc.max_size() / 2; }

		bool empty() const
		{ return _size ? false : true; }

		allocator_type get_allocator() const
		{ return _alloc; }

		key_compare key_comp() const
		{ return _cmp; }

		value_compare value_comp() const
		{ return value_compare(_cmp); }

		const mapped_type &at(const key_type &key) const
		{ return at(key); }

		mapped_type &at(const key_type &key)
		{
			node *res = find_node(_tree, key);
			if (keyCmp(key, res->value.first) == EQUAL)
				return res->value.second;
			else
				throw std::out_of_range("map::at:  key not found");
		}

		mapped_type &operator[](const key_type key)
		{
			ft::pair<iterator, bool> res = insert(
					ft::make_pair(key, mapped_type()));
			return (*res.first).second;
		}

		size_t count(const key_type &key) const
		{
			node *res = find_node(_tree, key);
			return keyCmp(key, res->value.first) == EQUAL ? 1 : 0;
		}

		void clear()
		{
			if (_size)
			{
				delete_tree(_tree);
				_tree = new node();
				_beginNode = _endNode = _tree;
				_size = 0;
			}
		}

		iterator find(const key_type &key)
		{
			node *res = find_node(_tree, key);
			return keyCmp(res->value.first, key) == EQUAL ? iterator(res)
														  : end();
		}

		const_iterator find(const key_type &key) const
		{
			node *res = find_node(_tree, key);
			return keyCmp(res->value.first, key) == EQUAL ? const_iterator(res)
														  : cend();
		}

		iterator lower_bound(const key_type &key)
		{
			iterator it(find_node(_tree, key));
			if (keyCmp((*it).first, key) == LESS)
				++it;
			return it;
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator it(find_node(_tree, key));
			if (keyCmp((*it).first, key) == LESS)
				++it;
			return it;
		}

		iterator upper_bound(const key_type &key)
		{
			iterator it(find_node(_tree, key));
			int compare = keyCmp((*it).first, key);
			if (compare == LESS || compare == EQUAL)
				++it;
			return it;
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator it(find_node(_tree, key));
			int compare = keyCmp((*it).first, key);
			if (compare == LESS || compare == EQUAL)
				++it;
			return it;
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return ft::make_pair(iterator(lower_bound(key)),
								 iterator(upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator>
		equal_range(const key_type &key) const
		{
			return ft::make_pair(const_iterator(lower_bound(key)),
								 const_iterator(upper_bound(key)));
		}

		ft::pair<iterator, bool> insert(const_reference value)
		{
//			std::cout << value.first << " " << value.second << std::endl;
			node *newNode = find_node(_tree,
									  value.first);    /*    ищем место для добавления элемента    */
			if (_size && valueCmp(value, newNode->value) ==
							 EQUAL)    /*    если элемент уже существует    */
				return ft::make_pair(iterator(newNode), false);
			if (!_size)    /*    вставка самого первого элемента    */
			{
				newNode = new node(
						value);    /*    новый узел для вставки (корень всего дерева)    */
				newNode->right = _tree;    /*    указатель на .end()    */
				newNode->left = new node();    /*    указатель на .rend()    */
				newNode->right->isBegin = 0;
				newNode->left->isEnd = 0;
				newNode->left->parent = newNode->right->parent = newNode;
				_beginNode = newNode->left;    /*    указатель на начало депева (элемент перед первым)    */
				_tree = newNode;    /*     новый корень всего дерева    */
			} else    /*    newNode - родитель нового элемента!    */
			{
				if (valueCmp(value, newNode->value) ==
					LESS)    /*    вставка слева    */
				{
					if (newNode->left)    /*    если newNode - миинимальный элемент дерева    */
					{
						node *tmp = new node(
								value);    /*    новый узел для вставки (минимальный элемент)    */
						tmp->left = newNode->left;    /*    указатель на .rend()    */
						tmp->left->parent = tmp;
						tmp->parent = newNode;
						newNode->left = tmp;
					} else    /*    обычная вставка слева    */
					{
						newNode->left = new node(value);
						newNode->left->parent = newNode;
					}
					newNode = newNode->left;    /*    newNode - добавленный узел    */
				} else if (valueCmp(value, newNode->value) ==
						   GREATER)    /*    вставка справа    */
				{
					if (newNode->right)    /*    если newNode - максимальный элемент дерева    */
					{
						node *tmp = new node(
								value);    /*    новый узел для вставки (максимальный элемент)    */
						tmp->right = newNode->right;    /*    указатель на .end()    */
						tmp->right->parent = tmp;
						tmp->parent = newNode;
						newNode->right = tmp;
					} else    /*    обычная вставка справа    */
					{
						newNode->right = new node(value);
						newNode->right->parent = newNode;
					}
					newNode = newNode->right;    /*    newNode - добавленный узел    */
				}
				makeBalance(
						newNode);    /*    балансировка ветви от newNode до корня    */
			}
			_size++;
			return ft::make_pair(iterator(newNode), true);
		}

		void erase(iterator pos)
		{
			node *rm = pos.getNode(); /*    указатель на узел для длаления    */
			node *l = rm->left;    /*    указатель на левое поддерево узла 'rm'     */
			node *r = rm->right;    /*    указатель на правое поддерево узла 'rm'    */
			node *parent = rm->parent; /*    указатель на родителя 'rm'    */
			if (rm ==
				_beginNode->parent)    /*    удаляем минимальный элемент    */
			{
				if (_size == 1)
				{
					clear();
					_beginNode = _endNode = _tree = new node();
					return;
				}
				if (r) /*    если у 'rm' есть правое поддерево, то заменяем 'rm' на минимальный элемент из дерева 'r'    */
				{
					node *newBegin = find_min(r);
					if (parent)
						parent->left = r;
					else
						_tree = newBegin;
					r->parent = parent;
					newBegin->left = _beginNode;
					_beginNode->parent = newBegin;
				} else    /*    обычное удаление минимального элемента    */
				{
					parent->left = _beginNode;
					_beginNode->parent = parent;
				}
				if (parent)
					makeBalance(parent);
				delete rm;
				_size--;
				return;
			}
			if (rm ==
				_endNode->parent)    /*    удаляем максимальный элемент    */
			{
				if (l) /*    если у 'rm' есть левое поддерево, то заменяем 'rm' на максимальный элемент из дерева 'l'    */
				{
					node *newEnd = find_max(l);
					if (parent)
						parent->right = l;
					else
						_tree = newEnd;
					l->parent = parent;
					newEnd->right = _endNode;
					_endNode->parent = newEnd;
				} else    /*    обычное удаление максимального элемента    */
				{
					_endNode->parent = parent;
					parent->right = _endNode;
				}
				if (parent)
					makeBalance(parent);
				delete rm;
				_size--;
				return;
			}
			if (l)    /*    удаление элемента с левым поддеревом    */
			{
				node *replacement = find_max(
						l);    /* максимальный    элемент из левого поддерева для замены 'rm'    */
				if (replacement->parent == rm)
				{
					replacement->parent = parent;
					replacement->right = r;
					if (r)
						r->parent = replacement;
					if (parent)
					{
						if (parent->left == rm)
							parent->left = replacement;
						else
							parent->right = replacement;
					} else
						_tree = replacement;
					makeBalance(replacement);
					delete rm;
					_size--;
					return;
				}
				replacement->parent->right = replacement->left;
				if (replacement->left)
					replacement->left->parent = replacement->parent;
				replacement->left = l;
				l->parent = replacement;
				replacement->right = r;
				if (r)
					r->parent = replacement;
				replacement->parent = parent;
				if (parent)
				{
					if (parent->left == rm)
						parent->left = replacement;
					else
						parent->right = replacement;
				} else
					_tree = replacement;
				makeBalance(replacement);
			} else
			{
				if (parent->left == rm)
				{
					if ((parent->left = r))
						parent->left->parent = parent;
				} else if (parent->right == rm)
				{
					if ((parent->right = r))
						parent->right->parent = parent;
				}
				makeBalance(parent);
			}
			delete rm;
			_size--;
			return;
		}

		template<class _InputIt>
		void insert(_InputIt first, _InputIt last)
		{
			for (; first != last; ++first)
				insert(ft::make_pair(first->first, first->second));
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		size_t erase(const key_type &key)
		{
			node *node = find_node(_tree, key);

			if (keyCmp(node->value.first, key) == EQUAL)
			{
				erase(iterator(node));
				return 1;
			}
			return 0;
		}

		void swap(map &other)
		{
			if (this != &other)
			{
				node *treeTmp = this->_tree;
				node *beginTmp = this->_beginNode;
				node *endTmp = this->_endNode;
				size_t sizeTmp = this->_size;

				this->_tree = other._tree;
				this->_beginNode = other._beginNode;
				this->_endNode = other._endNode;
				this->_size = other._size;

				other._tree = treeTmp;
				other._beginNode = beginTmp;
				other._endNode = endTmp;
				other._size = sizeTmp;
			}
		}

		/*    SECONDARY FUNCTIONS    */
		int keyCmp(const key_type &key1,
				   const key_type &key2) const /*    сравнение ключей    */
		{
			return _cmp(key1, key2) + _cmp(key2, key1) *
									  2; /*    0(key1 == key2), 1(key1 < key2), 2(key1 > key2)    */
		}

		int valueCmp(const_reference val1,
					 const_reference val2) const /*    сравнение двух пар по ключу    */
		{
			return keyCmp(val1.first, val2.first);
		}

		size_t height(node *p)    /*    получение высоты поддерева    */
		{
			return p ? p->height : 0;
		}

		int b_factor(
				node *p)    /*    balance factor        (-1, 0 или 1) - поддерево сбалансированно    */
		{
			return height(p->right) -
				   height(p->left);    /*    (-2 или 2) - требуется балансировка левого или правого поддерева , соответственно    */
		}

		void fix_height(
				node *p)    /*    корректировка высоты поддерева после вставки или удаления узла    */
		{
			size_t hl = height(p->left);
			size_t hr = height(p->right);
			p->height = (hl > hr ? hl : hr) + 1;
		}

		/*    повороты вокруг узла, balance factor корого == 2 или == -2,
		т.е. возникает расбалансировка одного из поддеревьев    */

		node *
		rotate_right(node *p)    /*    правый поворот вокруг узла 'p'    */
		{
			node *q = p->left;    /*    узел, который после поворота займёт место 'p' и станет корнем данного поддерева    */
			/*    поворот    */
			p->left = q->right;
			q->right = p;
			/*    меняем местами родителей повёрнутых узлов    */
			q->parent = p->parent;
			p->parent = q;
			if (q->right->left)
				q->right->left->parent = p;
			/*    корректировка высот новых поддеревьев    */
			fix_height(p);
			fix_height(q);
			return q;    /*    возвращаем новый корень данного поддерева    */
		}

		node *rotate_left(node *q)    /*    левый поворот вокруг узла 'q'    */
		{
			node *p = q->right;    /*    узел, который после поворота займёт место 'q' и станет корнем данного поддерева    */
			/*    поворот    */
			q->right = p->left;
			p->left = q;
			/*    меняем местами родителей повёрнутых узлов    */
			p->parent = q->parent;
			q->parent = p;
			if (p->left->right)
				p->left->right->parent = q;
			/*    корректировка высот новых поддеревьев    */
			fix_height(q);
			fix_height(p);
			return p;    /*    возвращаем новый корень данного поддерева    */
		}

		node *balance(node *p)    /*    балансировка узла 'p'    */
		{
			node *tmp = p->parent;    /*    запоминаем родителя данного узла    */
			fix_height(p);    /*    корректировка высоты данного поддерева    */
			if (b_factor(p) ==
				2)    /*    правое поддерево от 'p' выше левого    */
			{
				if (b_factor(p->right) <
					0)    /*    требуется поворот правого поддерева от 'p'    */
					p->right = rotate_right(p->right);
				if (!tmp)    /*    т.е. 'p' - корень всего дерева    */
					return _tree = rotate_left(
							p);    /*    балансировка корня всего дерева    */
				/*    балансировка поддерева с корнем 'p'    */
				if (tmp->left == p)
					return (tmp->left = rotate_left(p));
				else
					return (tmp->right = rotate_left(p));
			}
			if (b_factor(p) ==
				-2)    /*    левое поддерево от 'p' выше правого    */
			{
				if (b_factor(p->left) >
					0)    /*    требуется поворот левого поддерева от 'p'    */
					p->left = rotate_left(p->left);
				if (!tmp)    /*    т.е. 'p' - корень всего дерева    */
					return _tree = rotate_right(
							p);    /*    балансировка корня всего дерева    */
				/*    балансировка поддерева с корнем 'p'    */
				if (tmp->right == p)
					return (tmp->right = rotate_right(p));
				else
					return (tmp->left = rotate_right(p));
			}
			return p;    /*    балансировка не потребовалась    */
		}

		node *find_min(
				node *p)    /*    поиск узла с минимальным ключом в дереве 'p'    */
		{
			return p->left ? find_min(p->left) : p;
		}

		node *find_max(
				node *p)    /*    поиск узла с максимальным ключом в дереве 'p'    */
		{
			return p->right ? find_max(p->right) : p;
		}

		node *
		find_node(node *p, key_type k) const    /*    поиск узла по ключу    */
		{
			int compare = keyCmp(k, p->value.first);
			if (compare == LESS)
			{
				if (p->left && p->left != _beginNode)
					return find_node(p->left, k);
			} else if (compare == GREATER)
			{
				if (p->right && p->right != _endNode)
					return find_node(p->right, k);
			}
			return p;    /*    если узел с данным ключом отсутствует, то вернётся узел, ближайший по ключу    */
		}

		void delete_tree(node *p)    /*    очистка дерева    */
		{
			if (p->left != nullptr)
				delete_tree(p->left);
			if (p->right != nullptr)
				delete_tree(p->right);
			delete p;
		}

		void
		makeBalance(node *node)    /*    балансировка от node до корня    */
		{
			for (; node != nullptr; node = node->parent)
				node = balance(node);
		}

	};
}