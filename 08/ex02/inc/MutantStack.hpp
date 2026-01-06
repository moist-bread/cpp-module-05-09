#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <limits>
#include <stack>
#include <cstddef>

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


// -->┊( MUTANT STACK )┊.´-★☆★

template <typename T>
class MutantStack
{
public:
	MutantStack(void);					// default constructor
	MutantStack(MutantStack const &source);	// copy constructor
	~MutantStack(void);				// destructor
	
	MutantStack &operator=(MutantStack const &source);	// copy assignment

	bool empty(void) const;
	unsigned int size(void) const;
	T &top(void) const;
	void push(const T &val);
	void emplace(const T &val);
	void pop(void);
	void swap(std::stack<T> &source);
	
	std::stack<T> get_stack(void) const;

private:
	std::stack<T> _stack;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, MutantStack<T> const &source);
