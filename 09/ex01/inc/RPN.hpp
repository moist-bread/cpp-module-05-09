#ifndef RPN_HPP
#define RPN_HPP

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

// -->┊( RPN )┊.´-★☆★

class RPN
{
public:
	static void convert(std::string input);

private:
	RPN(void);	// default constructor
	RPN(RPN const &source);	// copy constructor
	~RPN(void);	// destructor
	RPN &operator=(RPN const &source);	// copy assignment operator overload
};

#endif