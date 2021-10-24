//
// Created by Nelson Amerei on 10/24/21.
//

namespace ft
{
//----------------------start of namespace

template <class T>
class Vector
{
public:

	typedef T * iterator;

	Vector();
	Vector(unsigned int size);
	Vector(unsigned int size, const T & initial);
	Vector(const Vector<T> & v);
	~Vector();

	unsigned int capacity() const;
	unsigned int size() const;
	bool empty() const;
	iterator begin();
	iterator end();
	T & front();
	T & back();
	void push_back(const T & value);
	void pop_back();

	void reserve(unsigned int capacity);
	void resize(unsigned int size);

	T & operator[](unsigned int index);
	Vector<T> & operator=(const Vector<T> &);

private:
	unsigned int _size;
	unsigned int _capacity;
	T * buffer;
	;
};

template<class T>
Vector<T>::Vector()
{
	_capacity = 0;
	_size = 0;
	buffer = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v)
{
	_size = v._size;
	_capacity = v._capacity;
	buffer = new T[_size];
	for (int i = 0; i < _size; i++)
	buffer[i] = v.buffer[i];
}

template<class T>
Vector<T>::Vector(unsigned int size)
{
	_capacity = size;
	_size = size;
	buffer = new T[size];
}

template<class T>
Vector<T>::Vector(unsigned int size, const T & initial)
{
	_size-size;
	_capacity = size;
	buffer = new T [size];
	for (int i = 0; i < size; i++)
	buffer[i] = initial;
	T();
}

template<class T>
Vector<T> & Vector<T>::operator = (const Vector<T> & v)
{
	delete[ ] buffer;
	_size = v._size;
	_capacity = v._capacity;
	buffer = new T [_size];
	for (int i = 0; i < _size; i++)
	buffer[i] = v.buffer[i];
	return *this;
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
	return buffer;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
	return buffer + size();
}

template<class T>
T& Vector<T>::Vector<T>::front()
{
	return buffer[0];
}

template<class T>
T& Vector<T>::Vector<T>::back()
{
	return buffer[size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v)
{
	if (_size >= _capacity)
		reserve(_capacity +5);
	buffer [_size++] = v;
}

template<class T>
void Vector<T>::pop_back()
{
	_size--;
}

template<class T>
void Vector<T>::reserve(unsigned int capacity)
	{
		if(buffer == 0)
	{
		_size = 0;
		_capacity = 0;
	}
	T * buffer = new T [capacity];
	assert(buffer);
	copy (buffer, buffer + _size, buffer);
	_capacity = capacity;
	delete[] buffer;
	buffer = buffer;

}

template<class T>
unsigned int Vector<T>::size()const//
{
	return _size;
}

template<class T>
void Vector<T>::resize(unsigned int size)
{
	reserve(size);
	size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index)
{
	return buffer[index];
}

template<class T>
unsigned int Vector<T>::capacity()const
{
	return _capacity;
}

template<class T>
Vector<T>::~Vector()
{
	delete[]buffer;
}

//----------------------end of namespace
}

#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#endif //FT_CONTAINERS_VECTOR_H
