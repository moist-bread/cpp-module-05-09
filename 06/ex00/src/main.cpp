#include "../inc/ScalarConverter.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   CONVERSION OF SCALAR TYPES 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./scalar [input]" << std::endl, 2);
	ScalarConverter::convert(av[1]);
	return (0);
}
