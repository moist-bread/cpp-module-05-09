#include "../inc/BitcoinExchange.hpp"
#include "../inc/Date.hpp"
#include "../inc/utils.tpp"

#include <fstream> // ifstream
#include <limits>
#include <iomanip>

std::map<Date, float> BitcoinExchange::_base_dataset;

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(BitcoinExchange const &source) { *this = source; }
BitcoinExchange::~BitcoinExchange(void) {}
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &source) { (void)source; return (*this); }

void BitcoinExchange::load_base_dataset(const std::string input)
{
	_base_dataset.clear();
	
	std::ifstream dataset_file(input.c_str(), std::ifstream::in);
	while (dataset_file.good())
	{
		std::string line;
		std::getline(dataset_file, line);
		if (!dataset_file.good() && line.empty())
			break;
		
		if (BitcoinExchange::_base_dataset.empty())
		{
			if (line != "date,exchange_rate")
				throw(std::runtime_error("reference data set is missing header: \"date,exchange_rate\""));
			std::getline(dataset_file, line);
			if (!dataset_file.good())
				throw(std::runtime_error("reference data set is missing data"));
		}
		
		try
		{
			std::pair<Date, float> set(BitcoinExchange::extract_date(line), BitcoinExchange::extract_value(line, 1));
			if (!(_base_dataset.insert(set)).second)
				throw(std::runtime_error("invalid repeated date"));
		}
		catch (const std::exception &e)
		{
			std::string error_msg = "reference data set has an ";
			error_msg += e.what();
			error_msg += ", line ";
			error_msg += var_to_str(_base_dataset.size() + 2);
			throw(std::runtime_error(error_msg.c_str()));
		}
	}

	if (DEBUG)
	{
		std::cout << CYN "-- Reference Data Set --" DEF << std::endl;
		std::cout << std::endl;
		for (std::map<Date, float>::const_iterator it = _base_dataset.begin(); it != _base_dataset.end(); it++)
			std::cout << it->first << "	" << std::fixed << std::setprecision(2) << it->second << std::endl;
		std::cout << std::endl;
	}
}

void BitcoinExchange::exchange_input(const std::string input)
{
	std::ifstream input_file(input.c_str(), std::ifstream::in);
	if (!input_file.is_open())
		throw(std::runtime_error("input file \"" + input + "\" was unable to be opened" ));
	
	bool header_found = false;

	while (input_file.good())
	{
		std::string line;
		std::getline(input_file, line);
		if (!input_file.good() && line.empty())
			break;
		
		if (!header_found)
		{
			if (line != "date | value")
				throw(std::runtime_error("input file is missing header: \"date | value\""));
			header_found = true;
			continue;
		}
		
		try
		{
			print_exchange(line);
		}
		catch (const std::exception &e)
		{
			std::cerr << RED "[ERROR] " DEF << e.what() << std::endl;
		}
	}
}

Date BitcoinExchange::extract_date(const std::string &input) 
{
	return (Date(input.substr(0, 10)));
}

#define NOT_SET -1

float BitcoinExchange::extract_value(const std::string &input, const unsigned int &separator_size)
{
	if (input.length() < 10 + separator_size + 1)
		throw(std::runtime_error("incorrectly formatted line"));

	int n = NOT_SET;
	float f = NOT_SET;
	bool is_int;

	try
	{
		n = str_to_num<int>(input.substr(10 + separator_size));
		is_int = true;
	}
	catch (const std::exception &e)
	{
		f = str_to_num<float>(input.substr(10 + separator_size));
		is_int = false;
	}

	if ((is_int && n < 0) || (!is_int && f < 0))
		throw(std::runtime_error("invalid negative value"));
	else if (input.find(".") == std::string::npos && !is_int)
		throw(std::runtime_error("invalid int overflow value"));
	
	return ((is_int ? static_cast<float>(n) : f));
}

void BitcoinExchange::print_exchange(const std::string &input)
{
	if (input.find(" | ") != 10)
		throw(std::runtime_error("incorrectly formatted line"));

	std::pair<Date, float> set(BitcoinExchange::extract_date(input), BitcoinExchange::extract_value(input, 3));

	if (set.first < _base_dataset.begin()->first)
		throw(std::runtime_error("invalid date " + var_to_str(set.first) + ", earlier than ref. dataset " + var_to_str(_base_dataset.begin()->first)));
	else if (set.second > 1000.0)
		throw(std::runtime_error("invalid value " + var_to_str(set.second) + ", bigger than 1000"));

	std::map<Date, float>::const_iterator match_exchange = _base_dataset.upper_bound(set.first);
	match_exchange--;
	
	std::cout << set.first << " => " << set.second << " = " <<  (match_exchange->second * set.second);
	
	if (DEBUG)
		std::cout << " date matched: " << match_exchange->first;
	
	std::cout << std::endl;
}
