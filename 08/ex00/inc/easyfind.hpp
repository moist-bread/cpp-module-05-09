#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <algorithm>

//-‵,┊ color defines

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define CYN "\e[0;36m"

#define DEF "\e[0m"

// -->┊( easyfind )┊.´-★☆★

template <typename T>
int easyfind(T container, int to_find)
{
	typename T::iterator it;

	it = std::find (container.begin(), container.end(), to_find);
	if (it != container.end())
		return (*it);
	else
		throw (std::out_of_range("couldn't find element in the container "));

}

template <typename T>
void print_container(T container)
{
	int idx = 1;
	for (typename T::iterator i = container.begin(); i != container.end(); i++)
		std::cout << BLU "elem " << idx++ << ": " DEF << *i << std::endl;
	std::cout << std::endl;
}
