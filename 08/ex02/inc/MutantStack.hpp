#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <stack>

//-‵,┊ color defines

#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define CYN "\e[0;36m"

#define URED "\e[4;31m"
#define UYEL "\e[4;33m"
#define UCYN "\e[4;36m"

#define DEF "\e[0m"

// -->┊( MUTANT STACK )┊.´-★☆★

template <typename T, class Container = std::deque<T> >
class MutantStack : public std::stack<T>
{
public:
	typedef typename MutantStack<T, Container>::container_type::iterator iterator;
	typedef typename MutantStack<T, Container>::container_type::const_iterator const_iterator;
	typedef typename MutantStack<T, Container>::container_type::reverse_iterator reverse_iterator;
	typedef typename MutantStack<T, Container>::container_type::const_reverse_iterator const_reverse_iterator;

	MutantStack(void);									  // default constructor
	MutantStack(MutantStack<T, Container> const &source); // copy constructor
	~MutantStack(void);									  // destructor

	MutantStack<T, Container> &operator=(MutantStack<T, Container> const &source); // copy assignment

	iterator begin(void) { return (this->c.begin()); };
	iterator end(void) { return (this->c.end()); };
	const_iterator cbegin(void) const { return (this->c.begin()); };
	const_iterator cend(void) const { return (this->c.end()); };
	reverse_iterator rbegin(void) { return (this->c.rbegin()); };
	reverse_iterator rend(void) { return (this->c.rend()); };
	const_reverse_iterator crbegin(void) const { return (this->c.rbegin()); };
	const_reverse_iterator crend(void) const { return (this->c.rend()); };

};

template <typename T, class Container>
std::ostream &operator<<(std::ostream &out, MutantStack<T, Container> &source);
