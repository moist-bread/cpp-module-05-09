#pragma once

//-‵,┊ needed libs by class
#include <iostream>

//-‵,┊ color defines

#define BLU "\e[0;34m"
#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( ITER )┊.´-★☆★

template <typename T>
void iter(T *array, const int len, void (*func)(T &elem))
{
	for (int i = 0; i < len; i++)
		func(array[i]);
}

template <typename T>
void printer(T &value)
{
	std::cout << "[ " << value <<" ]";
}

template <typename T>
void inc(T &value)
{
	value++;
}
