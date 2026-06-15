#include "../inc/BitcoinExchange.hpp"

std::map<std::string, float> BitcoinExchange::_base_dataset;

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

void BitcoinExchange::load_base_dataset(std::string input)
{
	std::cout << "BitcoinExchange dataset is loading... " << input << std::endl;

	std::ifstream dataset_file(input.c_str(), std::ifstream::in);
	while (dataset_file.good())
	{
		std::string line;
		std::getline(dataset_file, line);
		if (!dataset_file.good())
			throw(std::runtime_error("there was an error whilst reading the reference data set"));
		if (BitcoinExchange::_base_dataset.empty())
		{
			std::cout << "checking header" << std::endl;
			if (line != "date,exchange_rate")
				throw(std::runtime_error("reference data set is misisng header: \"date,exchange_rate\""));
			std::cout << "header was found" << std::endl;
		}
		else
		{
			try
			{
				BitcoinExchange::extract_date(line);
			}
			catch(const std::exception& e)
			{
				std::string error_msg = "reference data set has an ";
				error_msg += e.what();
				error_msg +=  " at line:";
				throw(std::runtime_error(error_msg.c_str()));
				std::cerr << e.what() << '\n';
			}
			
			// size_t year = 0; 
			// size_t month = 0; 
			// size_t day = 0; 
		}
		break;
	}

}

void BitcoinExchange::load_input(std::string input)
{
	std::cout << "BitcoinExchange input is loading... " << input << std::endl;
}

void BitcoinExchange::output_results(void)
{
	std::cout << "BitcoinExchange output!" << std::endl;
}

void BitcoinExchange::extract_date(std::string &input)
{
	std::cout << "BitcoinExchange input is extracting date... " << input << std::endl;
}
