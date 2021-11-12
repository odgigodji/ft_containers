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
			bool    operator!=(const iterator &rhs) { return this->_node != rhs._node; }
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
		~map() { del_tree(_base); }

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

		reverse_iterator	rbegin() { return --reverse_iterator(_lastNode); }
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
		mapped_type			&at(const key_type &k) {
			Node *res = findNode(_base, k);
			if (keyCompare(k, res->content.first) == IS_EQUAL) { return res->content.second; }
			else { throw std::out_of_range("map::at:  key not found"); }
		}

		mapped_type			&operator[](const key_type k) {
			ft::pair<iterator, bool> res = insert(ft::make_pair(k, mapped_type()));
			return (*res.first).second;
		}

		/*******************************************************************************
		*__________________________________Modifiers___________________________________*
		*******************************************************************************/
		ft::pair<iterator, bool>	insert(const_reference value) {
//			std::cout << value.first << " " << value.second << std::endl;
			Node *newNode = findNode(_base, value.first);    /*	find space for new node	*/
			/*							if node exist						*/
			if (_size && value_compare(value, newNode->content) == IS_EQUAL)
				return ft::make_pair(iterator(newNode), false);
			if (!_size) {
				newNode = new Node(value);
				newNode->right = _base;
				newNode->left = new Node();
				newNode->right->isBegin = newNode->left->isEnd = 0;
				newNode->left->parent = newNode->right->parent = newNode;
				_firstNode = newNode->left;
				_base = newNode;
			}
			else    	/*	"newNode" - parent of new element				*/
			{
				/* 					insert to left side*/
				if (value_compare(value, newNode->content) == IS_LESS) {
					if (newNode->left) /*newNode is min elem of tree*/
					{
						Node *t = new Node(value);
						t->left = newNode->left;
						t->left->parent = t;
						t->parent = newNode;
						newNode->left = t;
					}
					else {
						newNode->left = new Node(value);
						newNode->left->parent = newNode;
					}
					newNode = newNode->left;
				}
				/* 					insert to right side */
				else if (value_compare(value, newNode->content) == IS_GREATER) {
					if (newNode->right)	/* newNode - max elem of the tree */
					{
						Node *tmp = new Node( value);
						tmp->right = newNode->right;
						tmp->right->parent = tmp;
						tmp->parent = newNode;
						newNode->right = tmp;
					}
					else {
						newNode->right = new Node(value);
						newNode->right->parent = newNode;
					}
					newNode = newNode->right;
				}
				BalanceTree(newNode);		/*	balance tree from 'newNode' to root	*/
			}
			++_size;
			return ft::make_pair(iterator(newNode), true);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			for (; first != last; ++first) {
				insert(ft::make_pair(first->first, first->second));
			}
		}

		void insert (iterator position, const value_type& val) {
			;
		}

		void erase(iterator position)
		{
			Node *toDel = position.getNode();	/* node for delete */
			Node *left = toDel->left;
			Node *right = toDel->right;
			Node *parent = toDel->parent;
			/*							if min elem						*/
			if (toDel == _firstNode->parent)
			{
				if (_size == 1)
				{
					clear();
					_firstNode = _lastNode = _base = new Node();
					return;
				}
				if (right)	/* if have right	*/
				{
					Node *newBegin = findMinNode(right);
					if (parent)
						parent->left = right;
					else
						_base = newBegin;
					right->parent = parent;
					newBegin->left = _firstNode;
					_firstNode->parent = newBegin;
				} else
				{
					parent->left = _firstNode;
					_firstNode->parent = parent;
				}
				if (parent)
					BalanceTree(parent);
				delete toDel;
				_size--;
				return;
			}
			/*						if max elem							*/
			if (toDel == _lastNode->parent)
			{
				if (left)	/* if have right */
				{
					Node *newEnd = findMaxNode(left);
					if (parent) { parent->right = left; }
					else
						_base = newEnd;
					left->parent = parent;
					newEnd->right = _lastNode;
					_lastNode->parent = newEnd;
				} else
				{
					_lastNode->parent = parent;
					parent->right = _lastNode;
				}
				if (parent)
					BalanceTree(parent);
				delete toDel;
				_size--;
				return;
			}
			/*					delete elem with left sub tree				*/
			if (left)
			{
				Node *replace = findMaxNode(left);    /* максимальный    элемент из левого поддерева для замены 'rm'    */
				if (replace->parent == toDel)
				{
					replace->parent = parent;
					replace->right = right;
					if (right)
						right->parent = replace;
					if (parent)
					{
						if (parent->left == toDel)
							parent->left = replace;
						else
							parent->right = replace;
					} else
						_base = replace;
					BalanceTree(replace);
					delete toDel;
					--_size;
					return;
				}
				replace->parent->right = replace->left;
				if (replace->left)
					replace->left->parent = replace->parent;
				replace->left = left;
				left->parent = replace;
				replace->right = right;
				if (right)
					right->parent = replace;
				replace->parent = parent;
				if (parent)
				{
					if (parent->left == toDel)
						parent->left = replace;
					else
						parent->right = replace;
				} else
					_base = replace;
				BalanceTree(replace);
			}
			/*					delete elem with right sub tree				*/
			else
			{
				if (parent->left == toDel)
				{
					if ((parent->left = right)) { parent->left->parent = parent; }
				} else if (parent->right == toDel)
				{
					if ((parent->right = right))
						parent->right->parent = parent;
				}
				BalanceTree(parent);
			}
			delete toDel;
			--_size;
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		size_t erase(const key_type &k) {
			Node *node = findNode(_base, k);

			if (keyCompare(node->content.first, k) == IS_EQUAL) {
				erase(iterator(node));
				return 1;
			}
			return 0;
		}

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
		key_compare				key_comp() const { return _comp; }
		value_compare			value_comp() const { return value_compare(_comp); }

		/*******************************************************************************
		*__________________________________Operations__________________________________*
		*******************************************************************************/
		iterator find(const key_type &k) {
			Node *curr = findNode(_base, k);
			return keyCompare(curr->content.first, k) == IS_EQUAL ? iterator(curr) : end();
		}

		iterator find(const key_type &k) const {
			Node *curr = findNode(_base, k);
			return keyCompare(curr->content.first, k) == IS_EQUAL ? iterator(curr) : end();
		}

		size_t count(const key_type &k) const {
			Node *curr = findNode(_base, k);
			if (curr->content.first == k) { return 1; }
			return 0;
		}

		iterator lower_bound(const key_type &k) const {
			iterator iter(findNode(_base, k));
			if (keyCompare((*iter).first, k) == IS_LESS) { ++iter; }
			return iter;
		}
		iterator upper_bound(const key_type &k) const {
			iterator iter(findNode(_base, k));
			int compare = keyCompare((*iter).first, k);
			if (compare == IS_LESS || compare == IS_EQUAL) { ++iter; }
			return iter;
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key) const {
			return ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key)));
		}

		/*******************************************************************************
		*__________________________________Allocator___________________________________*
		*******************************************************************************/
		allocator_type            get_allocator() const { return _allocPair; }

		/*******************************************************************************
		*__________________________________Utilities___________________________________*
		*******************************************************************************/
		int keyCompare(const key_type &k1, const key_type &k2) const {
			/*				0(k1 == k2), 1(k1 < k2), 2(k1 > k2				*/
			return _comp(k1, k2) + _comp(k2, k1) * 2;
		}

		int value_compare(const_reference v1, const_reference v2) const {
			return keyCompare(v1.first, v2.first);
		}

		size_t subTreeHeight(Node *p) {
			return p ? p->height : 0;
		}

		/*	balance factor: -1, 0 or 1  tree is balanced	*/
		int balanceFactor(Node *p) {
			return subTreeHeight(p->right) - subTreeHeight(p->left);
		}

		void fixHeight(Node *p)
		{
			size_t hl = subTreeHeight(p->left);
			size_t hr = subTreeHeight(p->right);
			p->height = (hl > hr ? hl : hr) + 1;
		}

		/*				rotation if balance factor == 2 or -2				*/

		//               Q                                 P              |
		//              / \     RIGHT ROTATION            / \             |
		//             P   C  ------------------->>>     A   Q            |
		//            / \                                   / \           |
		//           A   B                                 B   C          |

		Node * rotateRight(Node *p) {
			Node *q = p->left;
			p->left = q->right;
			q->right = p;
			q->parent = p->parent;
			p->parent = q;
			if (q->right->left)
				q->right->left->parent = p;
			fixHeight(p);
			fixHeight(q);
			return q;
		}

		//               Q                                 P              |
		//              / \          LEFT ROTATION        / \             |
		//             P   C    <<<-------------------   A   Q            |
		//            / \                                   / \           |
		//           A   B                                 B   C          |

		Node *rotateLeft(Node *q) {
			Node *p = q->right;
			q->right = p->left;
			p->left = q;
			p->parent = q->parent;
			q->parent = p;
			if (p->left->right)
				p->left->right->parent = q;
			fixHeight(q);
			fixHeight(p);
			return p;					/* return new root*/
		}

		Node *balancingNode(Node *p) {
			Node *root = p->parent;						/*parent of current node*/
			fixHeight(p);								/*	fixheight root	*/
			if (balanceFactor(p) == 2)					/*	right branch height > left	*/
			{
				if (balanceFactor(p->right) < 0)		/*	need right rotate	*/
					p->right = rotateRight(p->right);
				if (!root)								/*	'root' - root of all tree	*/
					return _base = rotateLeft(p);		/*	balance root of all tree	*/
				/*	balance subTree with left	*/
				if (root->left == p)
					return (root->left = rotateLeft(p));
				else
					return (root->right = rotateLeft(p));
			}
			if (balanceFactor(p) == -2)
			{
				if (balanceFactor(p->left) > 0)
					p->left = rotateLeft(p->left);
				if (!root)
					return _base = rotateRight(p);
				if (root->right == p)
					return (root->right = rotateRight(p));
				else
					return (root->left = rotateRight(p));
			}
			return p;		/*	balance dont need	*/
		}

		Node *findMinNode(Node *p) { return p->left ? findMinNode(p->left) : p; }
		Node *findMaxNode( Node *p) { return p->right ? findMaxNode(p->right) : p; }

		Node * findNode(Node *p, key_type k) const
		{
			int compare = keyCompare(k, p->content.first);
			if (compare == IS_LESS)
			{
				if (p->left && p->left != _firstNode)
					return findNode(p->left, k);
			} else if (compare == IS_GREATER)
			{
				if (p->right && p->right != _lastNode)
					return findNode(p->right, k);
			}
			return p;/* if node not exist return node hwo closer for key*/
		}

		void del_tree(Node *p) {
			if (p->left != nullptr) { del_tree(p->left); }
			if (p->right != nullptr) { del_tree(p->right); }
			delete p;
		}

		void BalanceTree(Node *node) {
			for (; node != nullptr; node = node->parent) { node = balancingNode(node); }
		}
	};

	template < class Key, class T, class Compare, class Allocator >
	bool    operator==(const ft::map<Key, T, Compare, Allocator> &lhs,
			const ft::map<Key, T, Compare, Allocator> &rhs) {
		if (lhs.size() == rhs.size()) {

			return true;
		}
		return false;
	}
}