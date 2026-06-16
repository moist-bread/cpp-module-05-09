#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

//-‵,┊ needed libs by class
#include <string>
#include <map>

//-‵,┊ color defines

#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define CYN "\e[0;36m"
#define DEF "\e[0m"


# ifndef DEBUG
#  define DEBUG 0
# endif

class Date;

// -->┊( BITCOIN EXCHANGE )┊.´-★☆★

class BitcoinExchange
{
public:
	static void load_base_dataset(const std::string input);
	static void exchange_input(const std::string input);

private:
	BitcoinExchange(void);									   // default constructor
	BitcoinExchange(BitcoinExchange const &source);			   // copy constructor
	~BitcoinExchange(void);									   // destructor
	BitcoinExchange &operator=(BitcoinExchange const &source); // copy assignment operator overload

	static std::map<Date, float> _base_dataset;

	static Date extract_date(const std::string &input);
	static float extract_value(const std::string &input, const unsigned int &separator_size);
	static void print_exchange(const std::string &input);
};

#endif
