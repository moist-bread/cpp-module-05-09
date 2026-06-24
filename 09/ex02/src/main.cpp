#include "../inc/PmergeMe.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   PMERGE ME 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac < 2)
		return (std::cout << "usage: ./PmergeMe [number] [number] (...)" << std::endl, 2);
	try
	{
		PmergeMe sorting(&av[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << RED "[ERROR] " DEF << e.what() << std::endl;
		return (1);
	}
	return (0);
}
