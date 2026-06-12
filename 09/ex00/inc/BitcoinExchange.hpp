#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <map>
#include <stdlib.h>

//-‵,┊ color defines

#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( BITCOIN EXCHANGE )┊.´-★☆★

class BitcoinExchange
{
public:
	static void convert(std::string input);

private:
	BitcoinExchange(void);	// default constructor
	BitcoinExchange(BitcoinExchange const &source);	// copy constructor
	~BitcoinExchange(void);	// destructor
	BitcoinExchange &operator=(BitcoinExchange const &source);	// copy assignment operator overload
};

#endif