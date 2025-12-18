#pragma once

//-‵,┊ needed libs by class
#include "../inc/Array.hpp"

//-‵,┊ color defines

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"

#define URED "\e[4;31m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"

#define DEF "\e[0m"

// -->┊( ARRAY TEMPLATE METHODS )┊.´-★☆★

template <typename T>
Array<T>::Array (void): _array(NULL), _size(0)
{
	std::cout << GRN "an empty array of type [ " << typeid(T).name() << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

template <typename T>
Array<T>::Array (unsigned int n): _array(new T[n]), _size(n)
{
	std::cout << GRN "an array of type [ " << typeid(T).name() << " ] ";
	std::cout << "and length [ " << _size << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

template <typename T>
Array<T>::Array (Array const &source)
{
	_array = NULL;
	*this = source;
	std::cout << GRN "an array of type [ " << typeid(T).name() << " ] ";
	std::cout << "and length [ " << _size << " ] ";
	std::cout << UYEL "has been copy created" DEF << std::endl;
}

template <typename T>
Array<T>::~Array (void)
{
	delete[] _array;
	std::cout << GRN "an array of type [ " << typeid(T).name() << " ] ";
	std::cout << "and length [ " << _size << " ] ";
	std::cout << URED "has been deleted" DEF << std::endl;
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
	{
		_size = source.size();
		delete[] _array;
		_array = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			_array[i] = source._array[i]; 
	}
	return (*this);
}

template <typename T>
T &Array<T>::operator[](unsigned int idx)
{
	if (idx < 0 || idx >= _size)
		throw(std::out_of_range("out of range detected..."));
	return (_array[idx]);
}

template<typename T>
unsigned int Array<T>::size(void)const
{
	return (_size);
}
