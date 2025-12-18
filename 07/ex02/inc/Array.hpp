#pragma once

//-‵,┊ needed libs by class
#include <iostream>

// -->┊( ARRAY )┊.´-★☆★

template <typename T>
class Array
{
public:
	Array (void); // default constructor
	Array (unsigned int n);
	Array (Array const &source); // copy constructor
	~Array (void); // destructor
	Array &operator=(Array const &source); // copy assignment operator overload
	T &operator[](int idx); // subscript operator

	unsigned int size (void) const;

private:
	T _array;
	unsigned int _size;
};
