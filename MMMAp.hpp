#pragma once

#include "ft.hpp"
# define IS_EQUAL		0
# define IS_LESS		1
# define IS_GREATER		2

namespace ft
{
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
			key_compare    _comp;

		public:
			explicit	value_compare(const key_compare &c) : _comp(c) {}
			bool		operator ()(const_reference val1, const_reference val2) const {
				return _comp(val1.first, val2.first);
			}
		};

		/*							Allocator for node 							*/
		typedef typename allocator_type::template rebind<Node>::other	allocator_rebind_node;

		/*******************************************************************************
		*____________________________________Variables_________________________________*
		*******************************************************************************/
	private:
		Node*									_base;
		allocator_type							_allocPair;
		Node*									_lastNode;
		Node*									_firstNode;
		size_t          						_size;
		key_compare								_comp;
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


		class reverse_iterator : public ft::reverse_iterator<iterator>
		{
		private:
			Node *_node;

			Node *find_min(Node *p) {
				return p->left ? find_min(p->left) : p;
			}

			Node *find_max(Node *p) {
				return p->right ? find_max(p->right) : p;
			}

		public:
			reverse_iterator() : _node(nullptr){}
			reverse_iterator(Node *ptr) : _node(ptr){}
			~reverse_iterator(){}
			reverse_iterator(const reverse_iterator &other) { *this = other; }

			Node *getNode() const { return _node; }
			reverse_iterator &operator=(const reverse_iterator &other) {
				_node = other._node;
				return *this;
			}

			bool operator==(const reverse_iterator &other) { return this->_node == other._node; }
			bool operator!=(const reverse_iterator &other) { return this->_node != other._node; }
			reference operator*() { return _node->value; }
			pointer operator->() { return &_node->value; }

			reverse_iterator &operator++() {
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

			reverse_iterator &operator--() {
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

			reverse_iterator operator++(int) {
				reverse_iterator tmp(_node);
				operator++();
				return tmp;;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp(_node);
				operator--();
				return tmp;
			}
		};

		/*******************************************************************************
		*===============================MEMBER_FUNCTIONS===============================*
		********************************************************************************
		*__________________________Constructors_and_destructor_________________________*
		*******************************************************************************/

		/*                            CONSTRUCTORS:									*/
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) :  _size(0) {
			_base = _allocNode.allocate(1);
			_allocNode.construct(_base);
			_firstNode = _lastNode = _base;
		}

		template <class InputIterator> map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) :  _size(0) {
			_base = _allocNode.allocate(1);
			_allocNode.construct(_base);
			_firstNode = _lastNode = _base;
			insert(first, last);
		}

		map(const map &x) : _size(0) {
			_base = _allocNode.allocate(1);
			_allocNode.construct(_base);
			_firstNode = _lastNode = _base;
			*this = x;
		}
								/*    DESTRUCTOR:    */
		~map() /* delete_tree(_tree);*/ {
			del_tree(_base);
		}

						/*    ASSIGNATION OPERATOR OVERLOAD:    */
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
		iterator	begin() { return _size ? ++iterator(_firstNode) : iterator(_firstNode); }
		iterator	end() { return iterator(_lastNode); }
		iterator	begin() const { return _size ? ++iterator(_firstNode) : iterator(_firstNode); }
		iterator	end() const { return iterator(_lastNode); }

		reverse_iterator	rbegin() { return --reverse_iterator(_lastNode); } //fixme
		reverse_iterator	rend() { return reverse_iterator(_firstNode); }

		/*******************************************************************************
		*_________________________________Capacity:____________________________________*
		*******************************************************************************/
		bool				empty() const { return !_size; }
		size_t				size() const { return _size; }
		size_t				max_size() const { return _allocPair.max_size() / 2; }

		/*******************************************************************************
		*______________________________Element_access__________________________________*
		*******************************************************************************/
		//at
		const mapped_type&	at(const key_type& key) const { return at(key); }

		mapped_type			&at(const key_type &key)
		{
			Node *res = findNode(_base, key);
			if (keyCmp(key, res->content.first) == IS_EQUAL)
				return res->content.second;
			else
				throw std::out_of_range("map::at:  key not found");
		}

		//	operator[]
		mapped_type			&operator[](const key_type key)
		{
			ft::pair<iterator, bool> res = insert(
					ft::make_pair(key, mapped_type()));
			return (*res.first).second;
		}

		/*******************************************************************************
		*__________________________________Modifiers___________________________________*
		*******************************************************************************/
		//void construct( pointer p, const_reference val );  value_type* , value_type&
		ft::pair<iterator, bool> insert(const_reference value)
		{
//			std::cout << value.first << " " << value.second << std::endl;
			Node *newNode = findNode(_base, value.first);    /*    ищем место для добавления элемента    */
			if (_size && value_compare(value, newNode->content) == IS_EQUAL)    /*    если элемент уже существует    */
				return ft::make_pair(iterator(newNode), false);
			if (!_size)    /*    вставка самого первого элемента    */
			{
				newNode = new Node(value);    /*    новый узел для вставки (корень всего дерева)    */
				newNode->right = _base;    /*    указатель на .end()    */
				newNode->left = new Node();    /*    указатель на .rend()    */
				newNode->right->isBegin = 0;
				newNode->left->isEnd = 0;
				newNode->left->parent = newNode->right->parent = newNode;
				_firstNode = newNode->left;    /*    указатель на начало депева (элемент перед первым)    */
				_base = newNode;    /*     новый корень всего дерева    */
			}
			else    /*    newNode - родитель нового элемента!    */
			{
				if (value_compare(value, newNode->content) == IS_LESS)    /*    вставка слева    */
				{
					if (newNode->left)    /*    если newNode - миинимальный элемент дерева    */
					{
						Node *tmp = new Node(value);    /*    новый узел для вставки (минимальный элемент)    */
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
				} else if (value_compare(value, newNode->content) == IS_GREATER)    /*    вставка справа    */
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
		void erase(iterator position)
		{
			Node *curr = position.getNode(); /*    указатель на узел для удаления    */
			Node *left = curr->left;    /*    указатель на левое поддерево узла 'rm'     */
			Node *right = curr->right;    /*    указатель на правое поддерево узла 'rm'    */
			Node *parent = curr->parent; /*    указатель на родителя 'rm'    */
			if (curr == _firstNode->parent)    /*    удаляем минимальный элемент    */
			{
				if (_size == 1)
				{
					clear();
					_firstNode = _lastNode = _base = new Node();
					return;
				}
				if (right) /*    если у 'rm' есть правое поддерево, то заменяем 'rm' на минимальный элемент из дерева 'r'    */
				{
					Node *newBegin = findMinNode(right);
					if (parent)
						parent->left = right;
					else
						_base = newBegin;
					right->parent = parent;
					newBegin->left = _firstNode;
					_firstNode->parent = newBegin;
				} else    /*    обычное удаление минимального элемента    */
				{
					parent->left = _firstNode;
					_firstNode->parent = parent;
				}
				if (parent)
					makeBalance(parent);
				delete curr;
				_size--;
				return;
			}
			if (curr == _lastNode->parent)    /*    удаляем максимальный элемент    */
			{
				if (left) /*    если у 'rm' есть левое поддерево, то заменяем 'rm' на максимальный элемент из дерева 'l'    */
				{
					Node *newEnd = findMaxNode(left);
					if (parent)
						parent->right = left;
					else
						_base = newEnd;
					left->parent = parent;
					newEnd->right = _lastNode;
					_lastNode->parent = newEnd;
				} else    /*    обычное удаление максимального элемента    */
				{
					_lastNode->parent = parent;
					parent->right = _lastNode;
				}
				if (parent)
					makeBalance(parent);
				delete curr;
				_size--;
				return;
			}
			if (left)    /*    удаление элемента с левым поддеревом    */
			{
				Node *replacement = findMaxNode(left);    /* максимальный    элемент из левого поддерева для замены 'rm'    */
				if (replacement->parent == curr)
				{
					replacement->parent = parent;
					replacement->right = right;
					if (right)
						right->parent = replacement;
					if (parent)
					{
						if (parent->left == curr)
							parent->left = replacement;
						else
							parent->right = replacement;
					} else
						_base = replacement;
					makeBalance(replacement);
					delete curr;
					_size--;
					return;
				}
				replacement->parent->right = replacement->left;
				if (replacement->left)
					replacement->left->parent = replacement->parent;
				replacement->left = left;
				left->parent = replacement;
				replacement->right = right;
				if (right)
					right->parent = replacement;
				replacement->parent = parent;
				if (parent)
				{
					if (parent->left == curr)
						parent->left = replacement;
					else
						parent->right = replacement;
				} else
					_base = replacement;
				makeBalance(replacement);
			} else
			{
				if (parent->left == curr)
				{
					if ((parent->left = right))
						parent->left->parent = parent;
				} else if (parent->right == curr)
				{
					if ((parent->right = right))
						parent->right->parent = parent;
				}
				makeBalance(parent);
			}
			delete curr;
			_size--;
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		size_t erase(const key_type &k) {
			Node *node = findNode(_base, k);

			if (keyCmp(node->content.first, k) == IS_EQUAL) {
				erase(iterator(node));
				return 1;
			}
			return 0;
		}
		//swap
		void swap(map &x) {
			if (this != &x) {
				Node *tmp_base = _base;
				Node *firstTmp = _firstNode;
				Node *lastTmp = _lastNode;
				size_t sizeTmp = _size;

				_base = x._base;
				_firstNode = x._firstNode;
				_lastNode = x._lastNode;
				_size = x._size;

				x._base = tmp_base;
				x._firstNode = firstTmp;
				x._lastNode = lastTmp;
				x._size = sizeTmp;
			}
		}
		//clear
		void clear() {
			if (_size) {
				del_tree(_base);
				_base = new Node();
				_size = 0;
				_firstNode = _lastNode = _base;
			}
		}

		/*******************************************************************************
		*__________________________________Observers___________________________________*
		*******************************************************************************/
		//key_comp
		key_compare				key_comp() const { return _comp; }
		//value_comp
		value_compare			value_comp() const { return value_compare(_comp); }

		/*******************************************************************************
		*__________________________________Operations__________________________________*
		*******************************************************************************/
		//find
		iterator find(const key_type &k) {
			Node *curr = findNode(_base, k);
			return keyCmp(curr->content.first, k) == IS_EQUAL ? iterator(curr) : end();
		}

		iterator find(const key_type &k) const {
			Node *curr = findNode(_base, k);
			return keyCmp(curr->content.first, k) == IS_EQUAL ? iterator(curr) : end();
		}

		//count
		size_t count(const key_type &k) const {
			Node *curr = findNode(_base, k);
			if (curr->content.first == k) { return 1; }
			return 0;
		}
		//lower_bound

		iterator lower_bound(const key_type &k) const {
			iterator iter(findNode(_base, k));
			if (keyCmp((*iter).first, k) == IS_LESS) { ++iter; }
			return iter;
		}
		//upper_bound
		iterator upper_bound(const key_type &k) const {
			iterator iter(findNode(_base, k));
			int compare = keyCmp((*iter).first, k);
			if (compare == IS_LESS || compare == IS_EQUAL) { ++iter; }
			return iter;
		}

		//equal_range
		ft::pair<iterator, iterator> equal_range(const key_type &key) const {
			return ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key)));
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
//			std::cout << "key1 =" << key1 << "|key2 = " << key2 << "|and _cmp=" << _cmp(key1, key2) << std::endl;
			/*    0(key1 == key2), 1(key1 < key2), 2(key1 > key2)    */
			return _comp(key1, key2) + _comp(key2, key1) * 2;
		}

		int value_compare(const_reference val1, const_reference val2) const /*    сравнение двух пар по ключу    */
		{
			return keyCmp(val1.first, val2.first);
		}

		size_t height(Node *p)    /*    получение высоты поддерева    */
		{
			return p ? p->height : 0;
		}

		int b_factor(Node *p)    /*    balance factor        (-1, 0 или 1) - поддерево сбалансированно    */
		{
			return height(p->right) - height(p->left);    /*    (-2 или 2) - требуется балансировка левого или правого поддерева , соответственно    */
		}

		void fix_height(Node *p)    /*    корректировка высоты поддерева после вставки или удаления узла    */
		{
			size_t hl = height(p->left);
			size_t hr = height(p->right);
			p->height = (hl > hr ? hl : hr) + 1;
		}

		/*    повороты вокруг узла, balance factor корого == 2 или == -2,
		т.е. возникает расбалансировка одного из поддеревьев    */

		//
		//               Q                                 P              |
		//              / \     RIGHT ROTATION            / \             |
		//             P   C  ------------------->>>     A   Q            |
		//            / \                                   / \           |
		//           A   B                                 B   C          |

		Node * rotateRight(Node *p)    /*    правый поворот вокруг узла 'p'    */
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

		//
		//
		//               Q                                 P              |
		//              / \          LEFT ROTATION        / \             |
		//             P   C    <<<-------------------   A   Q            |
		//            / \                                   / \           |
		//           A   B                                 B   C          |

		Node *rotateLeft(Node *q)    /*    левый поворот вокруг узла 'q'    */
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
			if (b_factor(p) == 2)    /*    правое поддерево от 'p' выше левого    */
			{
				if (b_factor(p->right) < 0)    /*    требуется поворот правого поддерева от 'p'    */
					p->right = rotateRight(p->right);
				if (!tmp)    /*    т.е. 'p' - корень всего дерева    */
					return _base = rotateLeft(p);    /*    балансировка корня всего дерева    */
				/*    балансировка поддерева с корнем 'p'    */
				if (tmp->left == p)
					return (tmp->left = rotateLeft(p));
				else
					return (tmp->right = rotateLeft(p));
			}
			if (b_factor(p) == -2)    /*    левое поддерево от 'p' выше правого    */
			{
				if (b_factor(p->left) > 0)    /*    требуется поворот левого поддерева от 'p'    */
					p->left = rotateLeft(p->left);
				if (!tmp)    /*    т.е. 'p' - корень всего дерева    */
					return _base = rotateRight(p);    /*    балансировка корня всего дерева    */
				/*    балансировка поддерева с корнем 'p'    */
				if (tmp->right == p)
					return (tmp->right = rotateRight(p));
				else
					return (tmp->left = rotateRight(p));
			}
			return p;    /*    балансировка не потребовалась    */
		}

		Node *findMinNode(Node *p) { return p->left ? findMinNode(p->left) : p; }

		Node *findMaxNode( Node *p) { return p->right ? findMaxNode(p->right) : p; }

		Node * findNode(Node *p, key_type k) const    /*    поиск узла по ключу    */
		{
			int compare = keyCmp(k, p->content.first);
			if (compare == IS_LESS)
			{
				if (p->left && p->left != _firstNode)
					return findNode(p->left, k);
			} else if (compare == IS_GREATER)
			{
				if (p->right && p->right != _lastNode)
					return findNode(p->right, k);
			}
			return p;    /*    если узел с данным ключом отсутствует, то вернётся узел, ближайший по ключу    */
		}

		void del_tree(Node *p)    /*    очистка дерева    */
		{
			if (p->left != nullptr)
				del_tree(p->left);
			if (p->right != nullptr)
				del_tree(p->right);
			delete p;
		}

		void makeBalance(Node *node)    /*    балансировка от node до корня    */
		{
			for (; node != nullptr; node = node->parent)
				node = balance(node);
		}
	};
}