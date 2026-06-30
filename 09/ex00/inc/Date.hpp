#ifndef DATE_HPP
#define DATE_HPP

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <exception>

//-‵,┊ color defines

#define BLU "\e[0;34m"
#define DEF "\e[0m"

// -->┊( DATE )┊.´-★☆★

class Date
{
public:
	Date(void); // default
	Date(std::string input);
	Date(Date const &source); // copy
	~Date(void); // destructor
	Date &operator=(Date const &source); // copy assignment

	// operators
	bool operator>(Date const &src) const;
	bool operator<(Date const &src) const;
	bool operator>=(Date const &src) const;
	bool operator<=(Date const &src) const;
	bool operator==(Date const &src) const;
	bool operator!=(Date const &src) const;
	
	// getters
	const short &get_year(void) const;
	const short &get_month(void) const;
	const short &get_day(void) const;
	
	class InvalidDate : public std::runtime_error
	{
	public:
		InvalidDate(const std::string &date) : runtime_error("invalid date \"" + date + "\"" ) {};
	};
	
private:
	void extract_date(std::string &input);
	void validate_date(void);
	static short get_days_in_month(const short &m, const short &y);

	short year;
	short month;
	short day;
};

std::ostream &operator<<(std::ostream &out, const Date &src);

#endif
