#include "../inc/RPN.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   REVERSE POLISH NOTATION 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./RPN [input]" << std::endl, 2);
	RPN::convert(av[1]);
	return (0);
}
