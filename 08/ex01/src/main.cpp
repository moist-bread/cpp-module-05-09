#include "../inc/Span.hpp"

#include <time.h>

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   SPAN 🔎🏴‍☠️" DEF;
	std::cout << std::endl << std::endl;
	if (ac != 3 && ac != 1)
		return (std::cerr << "usage: ./span [limit] [add amount]" << std::endl, 2);
	
	int limit = 10;
	int add = 4;
	if (ac == 3)
	{
		limit = std::atoi(av[1]);
		add = std::atoi(av[2]);
	}
	srand(time(NULL));
	
	try
	{
		Span sp = Span(limit);
		for (int i = 0; i < add; i++)
			sp.addNumber(rand() % 100);
		std::cout << "\n-- created vector\n";
		std::cout << std::endl << sp << std::endl;
		std::cout << CYN "shortest span: " DEF << sp.shortestSpan() << std::endl;
		std::cout << CYN "longest span: " DEF << sp.longestSpan() << std::endl;
		sp.addNumber(rand() % 100);
		std::cout << "\n-- added an extra elem\n";
		std::cout << std::endl << sp << std::endl;
		sp.addRange(sp.get_span());
		std::cout << "\n-- added a range\n";
		std::cout << std::endl << sp << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << RED << e.what() << DEF << std::endl;
	}

	return (0);
}
