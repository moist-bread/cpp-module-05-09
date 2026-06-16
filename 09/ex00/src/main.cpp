#include "../inc/BitcoinExchange.hpp"

#include <iostream>

int main(int ac, char **av)
{
	std::cout << CYN "\n>>┈┈┈>   BITCOIN EXCHANGE 🔜🔎\n\n" DEF;

	if (ac != 2)
		return (std::cout << "usage: ./btc [input file]" << std::endl, 2);
	try
	{
		BitcoinExchange::load_base_dataset("./assets/data.csv");
		BitcoinExchange::exchange_input(av[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << RED "[ERROR] " DEF << e.what() << std::endl;
		return (1);
	}
	return (0);
}
