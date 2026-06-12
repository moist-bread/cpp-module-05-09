#include "../inc/PmergeMe.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   PMERGE ME 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./PmergeMe [input]" << std::endl, 2);
	PmergeMe::convert(av[1]);
	return (0);
}
