#include "../inc/RPN.hpp"

#include <iostream>

int main(int ac, char **av)
{
	std::cout << CYN "\n>>┈┈┈>   REVERSE POLISH NOTATION 🔜🔎\n\n" DEF;

	if (ac != 2)
		return (std::cout << "usage: ./btc [input file]" << std::endl, 2);
	try
	{
		RPN::process_expression(av[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << RED "[ERROR] " DEF << e.what() << std::endl;
		return (1);
	}
	return (0);
}
