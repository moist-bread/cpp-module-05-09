#include "../inc/MutantStack.hpp"

template <typename T, class Container>
MutantStack<T, Container>::MutantStack(void) : std::stack<T>()
{
	std::cout << GRN "a MutantStack " UCYN "has been created" DEF << std::endl;
}

template <typename T, class Container>
MutantStack<T, Container>::MutantStack(MutantStack<T, Container> const &source) : std::stack<T>(source)
{
	std::cout << GRN "a MutantStack " UYEL "has been copy created" DEF << std::endl;
}

template <typename T, class Container>
MutantStack<T, Container>::~MutantStack(void)
{
	std::cout << GRN "a MutantStack " URED "has been deleted" DEF << std::endl;
}

template <typename T, class Container>
MutantStack<T, Container> &MutantStack<T, Container>::operator=(MutantStack<T, Container> const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
		this->c = source.c;
	return (*this);
}

template <typename T, class Container>
std::ostream &operator<<(std::ostream &out, MutantStack<T, Container> &source)
{
	if (source.empty())
		out << BLU "no elements in MutantStack" DEF << std::endl;
	int idx = 1;
	for (typename MutantStack<T, Container>::iterator i = source.begin(); i != source.end(); i++)
		out << BLU "elem " << idx++ << ": " DEF << *i << std::endl;
	return (out);
}
