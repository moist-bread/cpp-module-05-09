#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

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

// -->┊( PMERGE ME )┊.´-★☆★

class PmergeMe
{
public:
	static void convert(std::string input);

private:
	PmergeMe(void);	// default constructor
	PmergeMe(PmergeMe const &source);	// copy constructor
	~PmergeMe(void);	// destructor
	PmergeMe &operator=(PmergeMe const &source);	// copy assignment operator overload
};

#endif