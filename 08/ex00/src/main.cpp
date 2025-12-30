#include "../inc/easyfind.hpp"

#include <time.h>
#include <vector>
#include <list>
#include <deque>

int main()
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   EASY FIND 🔎🏴‍☠️" DEF;
	std::cout << std::endl << std::endl;

	srand(time(NULL));
	std::vector<int> container;
	// std::list<int> container;
	// std::deque<int> container;

	// -- creation
	for (int i = 0; i < 10; i++)
		container.push_back(rand() % 10);
	print_container(container);
	
	// -- finding
	int to_find = rand() % 10;
	try
	{
		int pos = easyfind(container, to_find);
		std::cout << GRN "found " << pos << " in the container";
	}
	catch (std::exception &e)
	{
		std::cerr << RED << e.what() << to_find;
	}
	std::cout << DEF << std::endl;
	return (0);
}
