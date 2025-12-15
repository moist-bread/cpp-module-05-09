#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <stdlib.h>

//-‵,┊ color defines

#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( DEFINES )┊.´-★☆★

/// @brief flags for input types
typedef enum s_type
{
	INVALID,
	CHAR,
	PSEUDO,
	INT,
	FLOAT,
	DOUBLE
} t_type;

// -->┊( SCALAR CONVERTER )┊.´-★☆★

class ScalarConverter
{
public:
	static void convert(std::string input);

private:
	ScalarConverter(void);	// default constructor
	ScalarConverter(ScalarConverter const &source);	// copy constructor
	~ScalarConverter(void);	// destructor
	ScalarConverter &operator=(ScalarConverter const &source);	// copy assignment operator overload
};
