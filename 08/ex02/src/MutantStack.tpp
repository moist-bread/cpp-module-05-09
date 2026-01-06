#include "../inc/MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack(void)
{
	std::cout << GRN "a MutantStack " UCYN "has been created" DEF << std::endl;
}

template <typename T>
MutantStack<T>::MutantStack(MutantStack const &source)
{
	*this = source;
	std::cout << GRN "a MutantStack " UYEL "has been copy created" DEF << std::endl;
}

template <typename T>
MutantStack<T>::~MutantStack(void)
{
	std::cout << GRN "a MutantStack " URED "has been deleted" DEF << std::endl;
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(MutantStack<T> const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
		_stack = source.get_stack();
	return (*this);
}

template <typename T>
bool MutantStack<T>::empty(void) const
{
	return (_stack.empty());
}

template <typename T>
unsigned int MutantStack<T>::size(void) const
{
	return (_stack.size());
}

template <typename T>
T &MutantStack<T>::top(void) const
{
	return (_stack.top());
}

template <typename T>
void MutantStack<T>::push(const T &val)
{
	return (_stack.push(val));
}

template <typename T>
void MutantStack<T>::emplace(const T &val)
{
	return (_stack.emplace(val));
}

template <typename T>
void MutantStack<T>::pop(void)
{
	return (_stack.pop());
}

template <typename T>
void MutantStack<T>::swap(std::stack<T> &source)
{
	return (_stack.swap(source));
}

template <typename T>
std::stack<T> MutantStack<T>::get_stack(void) const
{
	return (_stack);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, MutantStack<T> const &source)
{
	int idx = 1;

	if (source.empty())
		out << BLU "no elements in MutantStack" DEF << std::endl;

	int_vec_t stack = source.get_stack();
	for (int_vec_t::iterator i = MutantStack.begin(); i != MutantStack.end(); i++)
		out << BLU "elem " << idx++ << ": " DEF << *i << std::endl;
	return (out);
}
