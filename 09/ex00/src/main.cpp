#include "../inc/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   BITCOIN EXCHANGE 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./btc [input file]" << std::endl, 2);
	try
	{
		BitcoinExchange::load_base_dataset("./assets/data.csv");
		BitcoinExchange::load_input(av[1]);
		BitcoinExchange::output_results();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED "[ERROR] " DEF << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}
