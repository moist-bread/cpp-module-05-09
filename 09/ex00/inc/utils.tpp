#ifndef UTILS_TPP
#define UTILS_TPP

#include <sstream> // stringstream


template <typename T>
T str_to_num(const std::string &str)
{
	std::stringstream ss(str);	
	T num;

	ss >> base >> num;
	if (ss.fail() || !ss.eof())
		throw (std::runtime_error("invalid number"));
	return (num);
}

#endif
