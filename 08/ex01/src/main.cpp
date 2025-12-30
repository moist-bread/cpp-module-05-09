#include "../inc/Span.hpp"

#include <time.h>
#include <vector>
#include <list>
#include <deque>

int main()
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   SPAN 🔎🏴‍☠️" DEF;
	std::cout << std::endl << std::endl;

	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp << std::endl;
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	return (0);
}
