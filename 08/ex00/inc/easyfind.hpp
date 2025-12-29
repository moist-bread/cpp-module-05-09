#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <typeinfo>
#include <stdexcept>

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

// -->┊( easyfind )┊.´-★☆★

template <typename T>
int easyfind(T container, int to_find)
{
	for (typename T::iterator i = container.begin(); i != container.end(); i++)
		if (*i == to_find)
			return (*i);
	throw(std::exception());
}

template <typename T>
void print_container(T container)
{
	int idx = 1;
	for (typename T::iterator i = container.begin(); i != container.end(); i++)
		std::cout << "elements " << idx++ << ": " << *i << std::endl;
	std::cout << std::endl;
}