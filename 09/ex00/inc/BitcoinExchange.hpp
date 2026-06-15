#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <map>
#include <stdlib.h>
#include <fstream> // ifstream

//-‵,┊ color defines

#define RED "\e[0;31m"
#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( BITCOIN EXCHANGE )┊.´-★☆★

class BitcoinExchange
{
public:
	static void load_base_dataset(std::string input);
	static void load_input(std::string input);
	static void output_results(void);
	
private:
	BitcoinExchange(void);	// default constructor
	BitcoinExchange(BitcoinExchange const &source);	// copy constructor
	~BitcoinExchange(void);	// destructor
	BitcoinExchange &operator=(BitcoinExchange const &source);	// copy assignment operator overload
	
	static std::map<std::string, float> _base_dataset;
	
	static void extract_date(std::string &input);
};

#endif