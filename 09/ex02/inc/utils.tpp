#ifndef UTILS_TPP
#define UTILS_TPP

#include <sstream> // stringstream

template <typename T>
T str_to_num(const std::string &str)
{
	std::stringstream ss(str);	
	T num;

	ss >> num;
	if (ss.fail() || !ss.eof())
		throw (std::runtime_error("invalid number \"" + str + "\""));
	return (num);
}

template <typename T>
std::string var_to_str(const T &value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
};


template <typename T>
typename T::iterator safe_advance(typename T::iterator it, const int distance, const T &list)
{
	if (distance > 0)
		for (int moved = 0; moved < distance && it != list.end(); moved++)
			it++;
	else if (distance < 0)
	{
		typename T::const_iterator limit = list.begin();
		limit--;
		for (int moved = 0; moved > distance && it != limit; moved--)
			it--;
	}
	return (it);
}

template <typename T>
typename T::iterator it_advance(typename T::iterator it, const int distance)
{
	if (distance > 0)
		for (int moved = 0; moved < distance; moved++)
			it++;
	else if (distance < 0)
		for (int moved = 0; moved > distance; moved--)
			it--;
	return (it);
}

template <typename T>
void pair_print(const T &array, const size_t pair_size)
{
	size_t i = 1;
	std::cout << BLK "\t";
	for (typename T::const_iterator it = array.begin(); it != array.end(); it++)
	{
		if (i == pair_size / 2)
			std::cout << CYN;

		if (i == pair_size)
		{
			std::cout << DEF "\r(b) " << *it << BLK "\t(s)\n\t";
			i = 0;
		}
		else
			std::cout << "\t" << *it;
		if (i == pair_size / 2)
			std::cout << BLK;
		i++;
	}
	std::cout << DEF "\n";
}

template <typename T>
void print_array(const T &array, std::string msg, const char *color)
{
	std::cout << color << "[ "<< msg << " ]\t" DEF;
	for (typename T::const_iterator it = array.begin(); it != array.end(); it++)
		std::cout << *it << " ";
	std::cout << ";\n";
}

#endif
