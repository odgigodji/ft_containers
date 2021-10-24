//
// Created by Nelson Amerei on 10/24/21.
//

#ifndef FT_CONTAINERS_ITERATORS_HPP
#define FT_CONTAINERS_ITERATORS_HPP

/*******************************************************************************
*-----------------------------------Iterator-----------------------------------*
*******************************************************************************/

class iterator : public ft::iterator_traits<std::random_access_iterator_tag, value_type>
{
private:
	pointer        _ptr{};

public:
	iterator() : _ptr(nullptr) {}
	iterator(pointer ptr) : _ptr(ptr) {}
	iterator(const iterator &other) { *this = other; }
	~iterator() {}
	iterator&        operator = (const iterator &other)
	{
		_ptr = other._ptr;
		return *this;
	}

	pointer            getPtr() const { return _ptr; }

	iterator&        operator ++ () { ++_ptr; return *this; }
	iterator&        operator -- () { --_ptr; return *this; }
	iterator        operator ++ (int) { return iterator(_ptr++); }
	iterator        operator -- (int) { return iterator(_ptr--); }
	iterator&        operator += (const difference_type &n) { _ptr += n; return *this; }
	iterator&        operator -= (const difference_type &n) { _ptr -= n; return *this; }
	iterator        operator + (const difference_type &n) const { return iterator(_ptr + n); }
	iterator        operator - (const difference_type &n) const { return iterator(_ptr - n); }
	reference        operator * () { return *_ptr; };
	difference_type    operator - (iterator const &other) const { return _ptr - other._ptr; }
	reference        operator [] (const_reference n) const { return _ptr[n]; }
	pointer            operator -> () { return _ptr; }

	bool            operator == (iterator const &other) const { return _ptr == other._ptr; }
	bool            operator != (iterator const &other) const { return _ptr != other._ptr; }
	bool            operator > (iterator const &other) const{ return _ptr > other._ptr; }
	bool            operator < (iterator const &other) const{ return _ptr < other._ptr; }
	bool            operator >= (iterator const &other) const { return _ptr >= other._ptr; }
	bool            operator <= (iterator const &other) const { return _ptr <= other._ptr; }
	bool            operator == (const_iterator const &other) const { return _ptr == other.getPtr(); }
	bool            operator != (const_iterator const &other) const { return _ptr != other.getPtr(); }
	bool            operator > (const_iterator const &other) const{ return _ptr > other.getPtr(); }
	bool            operator < (const_iterator const &other) const{ return _ptr < other.getPtr(); }
	bool            operator >= (const_iterator const &other) const { return _ptr >= other.getPtr(); }
	bool            operator <= (const_iterator const &other) const { return _ptr <= other.getPtr(); }
};
friend    iterator                operator + (const difference_type &n, const iterator &it) { return it + n; }


/*******************************************************************************
*-----------------------------Const Iterator-----------------------------------*
*******************************************************************************/

class const_iterator : public ft::iterator_traits<std::random_access_iterator_tag, const value_type>
{
private:
	pointer        _ptr;

public:
	const_iterator() : _ptr(nullptr) {}
	const_iterator(pointer ptr) : _ptr(ptr) {}
	~const_iterator() {}
	const_iterator(const const_iterator &other) { *this = other; }
	const_iterator(const iterator &other) { *this = other; }
	const_iterator&        operator = (const const_iterator &other)
	{
		_ptr = other._ptr;
		return *this;
	}

	const_iterator&        operator = (const iterator &other)
	{
		_ptr = other.getPtr();
		return *this;
	}

	const_pointer        getPtr() const { return _ptr; }

	const_iterator&        operator ++ () { ++_ptr; return *this; }
	const_iterator&        operator -- () { --_ptr; return *this; }
	const_iterator        operator ++ (int) { return const_iterator(_ptr++); }
	const_iterator        operator -- (int) { return const_iterator(_ptr--); }
	const_iterator&        operator += (difference_type n) { _ptr += n; return *this; }
	const_iterator&        operator -= (difference_type n) { _ptr -= n; return *this; }
	const_iterator        operator + (difference_type n) const { return const_iterator(_ptr + n); }
	const_iterator        operator - (difference_type n) const { return const_iterator(_ptr - n); }
	const_reference        operator * () const { return *_ptr; };
	difference_type        operator - (const_iterator const &other) const { return _ptr - other._ptr; }
	const_reference        operator [] (const_reference n) const { return _ptr[n]; }
	const_pointer        operator -> () const { return _ptr; }

	bool	operator == (const_iterator const &other) const { return _ptr == other._ptr; }
	bool	operator != (const_iterator const &other) const { return _ptr != other._ptr; }
	bool	operator > (const_iterator const &other) const{ return _ptr > other._ptr; }
	bool	operator < (const_iterator const &other) const{ return _ptr < other._ptr; }
	bool	operator >= (const_iterator const &other) const { return _ptr >= other._ptr; }
	bool	operator <= (const_iterator const &other) const { return _ptr <= other._ptr; }
	bool	operator == (iterator const &other) const { return _ptr == other.getPtr(); }
	bool	operator != (iterator const &other) const { return _ptr != other.getPtr(); }
	bool	operator > (iterator const &other) const{ return _ptr > other.getPtr(); }
	bool	operator < (iterator const &other) const{ return _ptr < other.getPtr(); }
	bool	operator >= (iterator const &other) const { return _ptr >= other.getPtr(); }
	bool	operator <= (iterator const &other) const { return _ptr <= other.getPtr(); }
};
friend    const_iterator            operator + (const difference_type &n, const const_iterator &it) { return it + n; }


/*******************************************************************************
*-----------------------------Reverse Iterator---------------------------------*
*******************************************************************************/

class reverse_iterator : public ft::reverse_iterator<iterator>
{
private:
	pointer        _ptr;

public:
	reverse_iterator() : _ptr(nullptr) {}
	reverse_iterator(pointer ptr) : _ptr(ptr) {}
	~reverse_iterator() {}
	reverse_iterator(const reverse_iterator &other) { *this = other; }
	reverse_iterator&    operator = (const reverse_iterator &other)
	{
		_ptr = other._ptr;
		return *this;
	}

	pointer                getPtr() const { return _ptr; }

	reverse_iterator&	operator ++ () { --_ptr; return *this; }
	reverse_iterator&	operator -- () { ++_ptr; return *this; }
	reverse_iterator	operator ++ (int) { return reverse_iterator(_ptr--); }
	reverse_iterator	operator -- (int) { return reverse_iterator(_ptr++); }
	reverse_iterator&	operator += (difference_type n) { _ptr -= n; return *this; }
	reverse_iterator&	operator -= (difference_type n) { _ptr += n; return *this; }
	reverse_iterator	operator + (difference_type n) const { return reverse_iterator(_ptr - n); }
	reverse_iterator	operator - (difference_type n) const { return reverse_iterator(_ptr + n); }
	reference        	operator * () const { return *_ptr; };
	difference_type		operator - (reverse_iterator const &other) const { return other._ptr - _ptr; }
	reference			operator [] (const_reference n) const { return _ptr[n]; }
	pointer				operator -> () { return _ptr; }

	bool	operator == (reverse_iterator const &other) const { return _ptr == other._ptr; }
	bool	operator != (reverse_iterator const &other) const { return _ptr != other._ptr; }
	bool	operator > (reverse_iterator const &other) const{ return _ptr > other._ptr; }
	bool	operator < (reverse_iterator const &other) const{ return _ptr < other._ptr; }
	bool	operator >= (reverse_iterator const &other) const { return _ptr >= other._ptr; }
	bool	operator <= (reverse_iterator const &other) const { return _ptr <= other._ptr; }
	bool	operator == (const_reverse_iterator const &other) const { return _ptr == other.getPtr(); }
	bool	operator != (const_reverse_iterator const &other) const { return _ptr != other.getPtr(); }
	bool	operator > (const_reverse_iterator const &other) const{ return _ptr > other.getPtr(); }
	bool	operator < (const_reverse_iterator const &other) const{ return _ptr < other.getPtr(); }
	bool	operator >= (const_reverse_iterator const &other) const { return _ptr >= other.getPtr(); }
	bool	operator <= (const_reverse_iterator const &other) const { return _ptr <= other.getPtr(); }
};
friend    const_reverse_iterator    operator + (const difference_type &n, const const_reverse_iterator &it) { return it + n; }


/*******************************************************************************
*--------------------------Const reverse Iterator------------------------------*
*******************************************************************************/

lass const_reverse_iterator : public ft::reverse_iterator<const_iterator>
{
private:
	pointer        _ptr;

public:
	const_reverse_iterator() : _ptr(nullptr) {}
	const_reverse_iterator(pointer ptr) : _ptr(ptr) {}
	~const_reverse_iterator() {}
	const_reverse_iterator(const const_reverse_iterator &other) { *this = other; }
	const_reverse_iterator(const reverse_iterator &other) { *this = other; }
	const_reverse_iterator&        operator = (const const_reverse_iterator &other)
	{
		if (this != &other)
			_ptr = other._ptr;
		return *this;
	}

	const_reverse_iterator&        operator = (const reverse_iterator &other)
	{
		_ptr = other.getPtr();
		return *this;
	}

	const_pointer                getPtr() const { return _ptr; }

	const_reverse_iterator&		operator ++ () { --_ptr; return *this; }
	const_reverse_iterator&		operator -- () { ++_ptr; return *this; }
	const_reverse_iterator		operator ++ (int) { return const_reverse_iterator(_ptr--); }
	const_reverse_iterator		operator -- (int) { return const_reverse_iterator(_ptr++); }
	const_reverse_iterator&		operator += (difference_type n) { _ptr -= n; return *this; }
	const_reverse_iterator&		operator -= (difference_type n) { _ptr += n; return *this; }
	const_reverse_iterator		operator + (difference_type n) const { return const_reverse_iterator(_ptr - n); }
	const_reverse_iterator		operator - (difference_type n) const { return const_reverse_iterator(_ptr + n); }
	const_reference				operator * () const { return *_ptr; };
	difference_type				operator - (const_reverse_iterator const &other) const { return other._ptr - _ptr; }
	const_reference				operator [] (const_reference n) const { return _ptr[n]; }
	const_pointer        		operator -> () const { return _ptr; }

	bool	operator == (const_reverse_iterator const &other) const { return _ptr == other._ptr; }
	bool	operator != (const_reverse_iterator const &other) const { return _ptr != other._ptr; }
	bool	operator > (const_reverse_iterator const &other) const{ return _ptr > other._ptr; }
	bool	operator < (const_reverse_iterator const &other) const{ return _ptr < other._ptr; }
	bool	operator >= (const_reverse_iterator const &other) const { return _ptr >= other._ptr; }
	bool	operator <= (const_reverse_iterator const &other) const { return _ptr <= other._ptr; }
	bool	operator == (reverse_iterator const &other) const { return _ptr == other.getPtr(); }
	bool	operator != (reverse_iterator const &other) const { return _ptr != other.getPtr(); }
	bool	operator > (reverse_iterator const &other) const{ return _ptr > other.getPtr(); }
	bool	operator < (reverse_iterator const &other) const{ return _ptr < other.getPtr(); }
	bool	operator >= (reverse_iterator const &other) const { return _ptr >= other.getPtr(); }
	bool	operator <= (reverse_iterator const &other) const { return _ptr <= other.getPtr(); }
};

friend    const_reverse_iterator    operator + (const difference_type &n, const const_reverse_iterator &it) { return it + n; }

#endif //FT_CONTAINERS_ITERATORS_HPP
