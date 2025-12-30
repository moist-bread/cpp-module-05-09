#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <algorithm>
#include <vector>

//-‵,┊ color defines

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"

#define URED "\e[4;31m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"

#define DEF "\e[0m"

typedef std::vector<int>	int_vec_t;

// -->┊( SPAN )┊.´-★☆★

class Span
{
public:
	Span(void);					// default constructor
	Span(unsigned int n);
	Span(Span const &source);	// copy constructor
	~Span(void);				// destructor
	
	Span &operator=(Span const &source);	// copy assignment
	
	void addNumber(int nbr);
	void addRange(int nbrs);
	int shortestSpan(void) const;
	int longestSpan(void) const;
	
	int_vec_t get_span(void) const;
	
private:
	int_vec_t _span;
	unsigned int N;
};

std::ostream &operator<<(std::ostream &out, Span const &source);
