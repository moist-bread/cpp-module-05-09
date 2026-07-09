#include "../inc/Date.hpp"
#include "../inc/utils.tpp"

#include <ctime> // time, localtime
#include <iomanip> // setfill, setw

Date::Date(void)
{
	time_t curr_time = std::time(NULL);
	struct tm datetime = *std::localtime(&curr_time);
	year = static_cast<short>(datetime.tm_year + 1900);
	month = static_cast<short>(datetime.tm_mon);
	day = static_cast<short>(datetime.tm_mday);
	validate_date();
}

Date::Date(std::string input)
{
	extract_date(input);
	validate_date();
}

Date::Date(Date const &src) { *this = src; }

Date::~Date(void) {}

Date &Date::operator=(Date const &src)
{
	if (this != &src)
	{
		year = src.get_year();
		month = src.get_month();
		day = src.get_day();
	}
	return (*this);
}

// !! comparison op

// -- tests
// std::cout << "today > " << av[1] << ": " << ((today > date) ? "true" : "false") << std::endl;
// std::cout << "today < " << av[1] << ": " << ((today < date) ? "true" : "false") << std::endl;
// std::cout << "today >= " << av[1] << ": " << ((today >= date) ? "true" : "false") << std::endl;
// std::cout << "today <= " << av[1] << ": " << ((today <= date) ? "true" : "false") << std::endl;
// std::cout << "today == " << av[1] << ": " << ((today == date) ? "true" : "false") << std::endl;
// std::cout << "today != " << av[1] << ": " << ((today != date) ? "true" : "false") << std::endl;

bool Date::operator>(Date const &src) const
{
	return (year > src.get_year() || \
	(year == src.get_year() && month > src.get_month()) || \
	(year == src.get_year() && month == src.get_month() && day > src.get_day())); 
}

bool Date::operator<(Date const &src) const
{
	return (year < src.get_year() || \
	(year == src.get_year() && month < src.get_month()) || \
	(year == src.get_year() && month == src.get_month() && day < src.get_day())); 
}

bool Date::operator>=(Date const &src) const { return (!(*this < src)); }

bool Date::operator<=(Date const &src) const { return (!(*this > src)); }

bool Date::operator==(Date const &src) const { return (year == src.get_year() && month == src.get_month() && day == src.get_day()); }

bool Date::operator!=(Date const &src) const { return (!(*this == src)); }

// !! basic getters

const short &Date::get_year(void) const { return (year); }
const short &Date::get_month(void) const { return (month); }
const short &Date::get_day(void) const { return (day); }

void Date::extract_date(std::string &input)
{
	if (input.length() != 10)
		throw(Date::InvalidDate(input));
	if (input.find("-") != 4 && input.rfind("-") != 7)
		throw(Date::InvalidDate(input));
	year = str_to_num<short>(input.substr(0,4));
	month = str_to_num<short>(input.substr(5,2));
	day = str_to_num<short>(input.substr(8,2));
}

void Date::validate_date(void)
{
	if (year < 1)
		throw(InvalidDate("year " + var_to_str(year)));
	if (month < 1 || month > 12)
		throw(InvalidDate("month " + var_to_str(month)));
	if (day < 1 || day > Date::get_days_in_month(month, year))
		throw(InvalidDate("day " + var_to_str(day)));

}

short Date::get_days_in_month(const short &m, const short &y)
{
	const short dim[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (m == 2 && ((!(y % 4) && y % 100) || !(y % 400))) // feb && leap year
		return (29);
	else
		return (dim[m - 1]);
}

std::ostream &operator<<(std::ostream &out, const Date &src)
{
	out << BLU "[" DEF << std::setfill ('0');
	out << std::setw(4) << src.get_year() << BLU "-" DEF;
	out << std::setw(2) << src.get_month() << BLU "-" DEF;
	out << std::setw(2) << src.get_day() << BLU "]" DEF;
	return (out);
}
