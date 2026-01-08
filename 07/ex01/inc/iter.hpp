#pragma once

//-‵,┊ needed libs by class
#include <iostream>

//-‵,┊ color defines

#define BLU "\e[0;34m"
#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( ITER )┊.´-★☆★

template <typename T>
void iter(T *array, const unsigned int len, void (*func)(T &elem))
{
	for (unsigned int i = 0; i < len; i++)
		func(array[i]);
}

// tester function that prints
template <typename T>
void printer(T &value)
{
	std::cout << "[ " << value <<" ]";
}

// tester function that increments
template <typename T>
void inc(T &value)
{
	value++;
}
