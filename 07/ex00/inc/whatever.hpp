#pragma once

//-‵,┊ needed libs by class
#include <iostream>

//-‵,┊ color defines
#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( WHATEVER )┊.´-★☆★

template <typename T>
void swap(T &value1, T &value2)
{
	T temp = value1;
    value1 = value2;
	value2 = temp;
}

template <typename T>
T min(T value1, T value2)
{
	if (value1 < value2)
		return (value1);
	else
		return (value2);
}

template <typename T>
T max(T value1, T value2)
{
	if (value1 > value2)
		return (value1);
	else
		return (value2);
}
