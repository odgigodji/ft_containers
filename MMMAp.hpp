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
		struct	Node {
			value_type	content; 		/*    пара ключ - значение            */
			size_t		height;			/*    высота поддерева                */
			Node*		parent;			/*    указатель на родителя           */
			Node*		right;			/*    указатель на правое поддерево   */
			Node*		left; 			/*    указатель на левое поддерево    */
			bool		isBegin;		/*    true - узел перед минимальным	  */
			bool		isEnd;			/*    true - узел после максимального */

			/*   					NEW NODE CONSTRUCTORS :					  */
			Node() :							height(0),
												parent(nullptr),
												right(nullptr),
												left(nullptr),
												isBegin(true),
												isEnd(true) {}

			explicit Node(const_reference val):	content(ft::make_pair(val.first, val.second)),
											   	height(1),
											   	parent(nullptr),
											   	right(nullptr),
											   	left(nullptr),
											   	isBegin(false),
											   	isEnd(false) {}
			Node(const Node &orig) { *this = orig; }

			~Node() {};
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
		typedef typename allocator_type::template rebind<Node>::other	allocator_rebind_node;

		/*******************************************************************************
		*____________________________________Variables_________________________________*
		*******************************************************************************/
	private:
		Node*									_tree;
		size_t          						_size;
		allocator_type							_allocPair;
		Node*									_beginNode;
		Node*									_endNode;
		key_compare								_cmp;
		allocator_rebind_node					_allocNode;

		/*******************************************************************************
		*_______________________________Iterators_classes______________________________*
		*******************************************************************************/
	public:
		class iterator;

		class    iterator : public ft::iterator_traits<std::bidirectional_iterator_tag, value_type> {
		private:
			Node*	_node;

			Node*	find_min(Node *p) {
				return p->left ? find_min(p->left) : p;
			}
			Node*	find_max(Node *p) {
				return p->right ? find_max(p->right) : p;
			}

		public:
			iterator() : _node(nullptr) {}
			iterator(Node *ptr) : _node(ptr) {}
			~iterator() {}
			iterator(const iterator &other) { *this = other; }

			Node*			getNode() const { return _node; }

//ft::map<int, int, std::__1::greater<int>, std::__1::allocator<ft::pair<const int, int> > >::iterator
//const ft::map<int, int, std::__1::less<int>, std::__1::allocator<ft::pair<const int, int> > >::iterator

			iterator&		operator = (const iterator &other) {
				_node = other._node;
				return *this;
			}
			reference	operator*() { return _node->content; }
			pointer		operator->() { return &_node->content; }
			bool    operator==(const iterator &rhs) { return this->_node == rhs._node; }
			bool    operator!=(const iterator &hrs) { return this->_node != hrs._node; }

			iterator&    operator++() {
				if (_node->isBegin)
					_node = _node->parent;
				else if (_node->right)
					_node = find_min(_node->right);
				else {
					Node    *tmp = _node->parent;
					while (tmp && tmp->content.first < _node->content.first)
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
					Node    *tmp = _node->parent;
					while (tmp && tmp->content.first > _node->content.first)
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

		/*
		class reverse_iterator : public ft::reverse_iterator<iterator>
		{
		private:
			Node *_node;

			Node *find_min(Node *p)
			{ return p->left ? find_min(p->left) : p; }

			Node *find_max(Node *p)
			{ return p->right ? find_max(p->right) : p; }

		public:
			reverse_iterator() : _node(nullptr)
			{}

			reverse_iterator(Node *ptr) : _node(ptr)
			{}

			~reverse_iterator()
			{}

			reverse_iterator(const reverse_iterator &other)
			{ *this = other; }

			Node *getNode() const
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
					Node *tmp = _node->parent;
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
					Node *tmp = _node->parent;
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
		 */

		/*******************************************************************************
		*===============================MEMBER_FUNCTIONS===============================*
		********************************************************************************
		*__________________________Constructors_and_destructor_________________________*
		*******************************************************************************/

/*    CONSTRUCTORS    */
//std::__1::allocator<ft::map<int, int, std::__1::less<int>, std::__1::allocator<ft::pair<const int, int> > >::Node>::construct<ft::map<int, int, std::__1::less<int>,
//std::__1::allocator<ft::pair<const int, int> > >::Node>
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) :  _size(0) {
			_tree = _allocNode.allocate(1);
			_allocNode.construct(_tree);
			_beginNode = _endNode = _tree;
		}

		template <class InputIterator> map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) :  _size(0) {
			_tree = _allocNode.allocate(1);
			_allocNode.construct(_tree);
			_beginNode = _endNode = _tree;
			insert(first, last);
		}

		map(const map &x) : _size(0) {
			_tree = _allocNode.allocate(1);
			_allocNode.construct(_tree);
			_beginNode = _endNode = _tree;
			*this = x;
		}

/*    DESTRUCTOR    */
		~map() // delete_tree(_tree);
		{
			delete_tree(_tree);
//			_allocNode.destroy(_tree);
//			_allocNode.deallocate(_tree, 1);

		}

/*    ASSIGNATION OPERATOR OVERLOAD    */
		map &operator=(const map &x) {
			if (this != &x) {
				clear();
				insert(x.begin(), x.end());
			}
			return *this;
		}

		/*******************************************************************************
		*__________________________________Iterators___________________________________*
		*******************************************************************************/
		iterator            begin() { return _size ? ++iterator(_beginNode) : iterator(_beginNode); }
		iterator            end() { return iterator(_endNode); }
		iterator            begin() const { return _size ? ++iterator(_beginNode) : iterator(_beginNode); }
		iterator            end() const { return iterator(_endNode); }

//		iterator            cbegin() const { return _size ? ++iterator(_beginNode) : iterator(_beginNode); }
//		iterator            cend() const { return iterator(_endNode); }

//		reverse_iterator        rbegin() { return --reverse_iterator(_endNode); } //fixme
//		reverse_iterator        rend() { return reverse_iterator(_beginNode); }

//		reverse_iterator    rbegin() const { return --reverse_iterator(_endNode); }
//		reverse_iterator    rend() const { return reverse_iterator(_beginNode); }

//		reverse_iterator    crbegin() const { return --reverse_iterator(_endNode); }
//		reverse_iterator    crend() const { return reverse_iterator(_beginNode); }

		/*******************************************************************************
		*_________________________________Capacity:____________________________________*
		*******************************************************************************/
		bool				empty() const { return !_size; }
		size_t				size() const { return _size; }
		size_t				max_size() const { return _allocPair.max_size() / 2; }

		/*******************************************************************************
		*______________________________Element_access__________________________________*
		*******************************************************************************/
		//	operator[]
		const mapped_type&        at(const key_type& key) const { return at(key); }

		mapped_type &at(const key_type &key)
		{
			Node *res = find_node(_tree, key);
			if (keyCmp(key, res->content.first) == EQUAL)
				return res->content.second;
			else
				throw std::out_of_range("map::at:  key not found");
		}

		mapped_type &operator[](const key_type key)
		{
			ft::pair<iterator, bool> res = insert(
					ft::make_pair(key, mapped_type()));
			return (*res.first).second;
		}

		/*******************************************************************************
		*__________________________________Modifiers___________________________________*
		*******************************************************************************/
		ft::pair<iterator, bool> insert(const_reference value)
		{
//			std::cout << value.first << " " << value.second << std::endl;
			Node *newNode = find_node(_tree, value.first);    /*    ищем место для добавления элемента    */
			if (_size && valueCmp(value, newNode->content) == EQUAL)    /*    если элемент уже существует    */
				return ft::make_pair(iterator(newNode), false);
			if (!_size)    /*    вставка самого первого элемента    */
			{
				newNode = new Node(value);    /*    новый узел для вставки (корень всего дерева)    */
				newNode->right = _tree;    /*    указатель на .end()    */
				newNode->left = new Node();    /*    указатель на .rend()    */
				newNode->right->isBegin = 0;
				newNode->left->isEnd = 0;
				newNode->left->parent = newNode->right->parent = newNode;
				_beginNode = newNode->left;    /*    указатель на начало депева (элемент перед первым)    */
				_tree = newNode;    /*     новый корень всего дерева    */
			}
			else    /*    newNode - родитель нового элемента!    */
			{
				if (valueCmp(value, newNode->content) == LESS)    /*    вставка слева    */
				{
					if (newNode->left)    /*    если newNode - миинимальный элемент дерева    */
					{
						Node *tmp = new Node( value);    /*    новый узел для вставки (минимальный элемент)    */
						tmp->left = newNode->left;    /*    указатель на .rend()    */
						tmp->left->parent = tmp;
						tmp->parent = newNode;
						newNode->left = tmp;
					} else    /*    обычная вставка слева    */
					{
						newNode->left = new Node(value);
						newNode->left->parent = newNode;
					}
					newNode = newNode->left;    /*    newNode - добавленный узел    */
				} else if (valueCmp(value, newNode->content) == GREATER)    /*    вставка справа    */
				{
					if (newNode->right)    /*    если newNode - максимальный элемент дерева    */
					{
						Node *tmp = new Node( value);    /*    новый узел для вставки (максимальный элемент)    */
						tmp->right = newNode->right;    /*    указатель на .end()    */
						tmp->right->parent = tmp;
						tmp->parent = newNode;
						newNode->right = tmp;
					} else    /*    обычная вставка справа    */
					{
						newNode->right = new Node(value);
						newNode->right->parent = newNode;
					}
					newNode = newNode->right;    /*    newNode - добавленный узел    */
				}
				makeBalance( newNode);    /*    балансировка ветви от newNode до корня    */
			}
			_size++;
			return ft::make_pair(iterator(newNode), true);
		}


		template<class _InputIt>
		void insert(_InputIt first, _InputIt last)
		{
			for (; first != last; ++first)
				insert(ft::make_pair(first->first, first->second));
		}

		void insert (iterator position, const value_type& val) {
			;
		}

		//erase
		void erase(iterator pos)
		{
			Node *rm = pos.getNode(); /*    указатель на узел для длаления    */
			Node *l = rm->left;    /*    указатель на левое поддерево узла 'rm'     */
			Node *r = rm->right;    /*    указатель на правое поддерево узла 'rm'    */
			Node *parent = rm->parent; /*    указатель на родителя 'rm'    */
			if (rm ==
				_beginNode->parent)    /*    удаляем минимальный элемент    */
			{
				if (_size == 1)
				{
					clear();
					_beginNode = _endNode = _tree = new Node();
					return;
				}
				if (r) /*    если у 'rm' есть правое поддерево, то заменяем 'rm' на минимальный элемент из дерева 'r'    */
				{
					Node *newBegin = find_min(r);
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
					Node *newEnd = find_max(l);
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
				Node *replacement = find_max(
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

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		size_t erase(const key_type &key)
		{
			Node *node = find_node(_tree, key);

			if (keyCmp(node->content.first, key) == EQUAL)
			{
				erase(iterator(node));
				return 1;
			}
			return 0;
		}
		//swap
		void swap(map &other)
		{
			if (this != &other)
			{
				Node *treeTmp = this->_tree;
				Node *beginTmp = this->_beginNode;
				Node *endTmp = this->_endNode;
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
		//clear
		void clear()
		{
			if (_size)
			{
				delete_tree(_tree);
				_tree = new Node();
				_beginNode = _endNode = _tree;
				_size = 0;
			}
		}

		/*******************************************************************************
		*__________________________________Observers___________________________________*
		*******************************************************************************/
		//key_comp
		//value_comp
		key_compare				key_comp() const { return _cmp; }
		value_compare			value_comp() const { return value_compare(_cmp); }

		/*******************************************************************************
		*__________________________________Operations__________________________________*
		*******************************************************************************/
		//find
		iterator find(const key_type &key) {
			Node *res = find_node(_tree, key);
			return keyCmp(res->content.first, key) == EQUAL ? iterator(res)
														  : end();
		}

		iterator find(const key_type &key) const {
			Node *res = find_node(_tree, key);
			return keyCmp(res->content.first, key) == EQUAL ? iterator(res)
														  : end();
		}
		//count
		size_t count(const key_type &key) const {
			Node *res = find_node(_tree, key);
			return keyCmp(key, res->content.first) == EQUAL ? 1 : 0;
		}
		//lower_bound
		iterator lower_bound(const key_type &key) {
			iterator it(find_node(_tree, key));
			if (keyCmp((*it).first, key) == LESS)
				++it;
			return it;
		}

		iterator lower_bound(const key_type &key) const {
			iterator it(find_node(_tree, key));
			if (keyCmp((*it).first, key) == LESS)
				++it;
			return it;
		}
		//upper_bound
		iterator upper_bound(const key_type &key) {
			iterator it(find_node(_tree, key));
			int compare = keyCmp((*it).first, key);
			if (compare == LESS || compare == EQUAL)
				++it;
			return it;
		}

		iterator upper_bound(const key_type &key) const {
			iterator it(find_node(_tree, key));
			int compare = keyCmp((*it).first, key);
			if (compare == LESS || compare == EQUAL)
				++it;
			return it;
		}

		//equal_range
		ft::pair<iterator, iterator> equal_range(const key_type &key) {
			return ft::make_pair(iterator(lower_bound(key)),
								 iterator(upper_bound(key)));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key) const {
			return ft::make_pair(iterator(lower_bound(key)),
								 iterator(upper_bound(key)));
		}

		/*******************************************************************************
		*__________________________________Allocator___________________________________*
		*******************************************************************************/
		//get_allocator
		allocator_type            get_allocator() const { return _allocPair; }

		/*******************************************************************************
		*__________________________________Utilities___________________________________*
		*******************************************************************************/






		/*    SECONDARY FUNCTIONS    */
		int keyCmp(const key_type &key1, const key_type &key2) const /*    сравнение ключей    */
		{
			/*    0(key1 == key2), 1(key1 < key2), 2(key1 > key2)    */
			return _cmp(key1, key2) + _cmp(key2, key1) * 2;
		}

		int valueCmp(const_reference val1, const_reference val2) const /*    сравнение двух пар по ключу    */
		{
			return keyCmp(val1.first, val2.first);
		}

		size_t height(Node *p)    /*    получение высоты поддерева    */
		{
			return p ? p->height : 0;
		}

		int b_factor(
				Node *p)    /*    balance factor        (-1, 0 или 1) - поддерево сбалансированно    */
		{
			return height(p->right) -
				   height(p->left);    /*    (-2 или 2) - требуется балансировка левого или правого поддерева , соответственно    */
		}

		void fix_height(
				Node *p)    /*    корректировка высоты поддерева после вставки или удаления узла    */
		{
			size_t hl = height(p->left);
			size_t hr = height(p->right);
			p->height = (hl > hr ? hl : hr) + 1;
		}

		/*    повороты вокруг узла, balance factor корого == 2 или == -2,
		т.е. возникает расбалансировка одного из поддеревьев    */

		Node *
		rotate_right(Node *p)    /*    правый поворот вокруг узла 'p'    */
		{
			Node *q = p->left;    /*    узел, который после поворота займёт место 'p' и станет корнем данного поддерева    */
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

		Node *rotate_left(Node *q)    /*    левый поворот вокруг узла 'q'    */
		{
			Node *p = q->right;    /*    узел, который после поворота займёт место 'q' и станет корнем данного поддерева    */
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

		Node *balance(Node *p)    /*    балансировка узла 'p'    */
		{
			Node *tmp = p->parent;    /*    запоминаем родителя данного узла    */
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

		Node *find_min(
				Node *p)    /*    поиск узла с минимальным ключом в дереве 'p'    */
		{
			return p->left ? find_min(p->left) : p;
		}

		Node *find_max(
				Node *p)    /*    поиск узла с максимальным ключом в дереве 'p'    */
		{
			return p->right ? find_max(p->right) : p;
		}

		Node *
		find_node(Node *p, key_type k) const    /*    поиск узла по ключу    */
		{
			int compare = keyCmp(k, p->content.first);
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

		void delete_tree(Node *p)    /*    очистка дерева    */
		{
			if (p->left != nullptr)
				delete_tree(p->left);
			if (p->right != nullptr)
				delete_tree(p->right);
			delete p;
		}

		void
		makeBalance(Node *node)    /*    балансировка от node до корня    */
		{
			for (; node != nullptr; node = node->parent)
				node = balance(node);
		}

	};
}