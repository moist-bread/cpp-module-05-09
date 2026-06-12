#include "../inc/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   BITCOIN EXCHANGE 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./btc [input file]" << std::endl, 2);
	BitcoinExchange::convert(av[1]);
	return (0);
}
