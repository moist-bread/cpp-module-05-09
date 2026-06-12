#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &source)
{
	*this = source;
}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

void BitcoinExchange::convert(std::string input)
{
	std::cout << "BitcoinExchange in process... " << input << std::endl;
}
