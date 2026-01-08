#include "../inc/MutantStack.hpp"
#include "../inc/MutantStack.tpp"

#include <algorithm>
#include <time.h>
#include <list>

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   MUTATED ABOMINATION 🔎🏴‍☠️" DEF;
	std::cout << std::endl << std::endl;

	if (ac != 3 && ac != 1)
		return (std::cerr << "usage: ./span [add] [remove]" << std::endl, 2);
	
	int add = 10;
	int rem = 4;
	if (ac == 3)
	{
		add = std::atoi(av[1]);
		rem = std::atoi(av[2]);
	}
	srand(time(NULL));

	MutantStack<int> mstack;
	std::cout << mstack;
	for (int i = 0; i < add; i++)
		mstack.push(rand() % 100);
	
	std::cout << "\n-- created stack\n";
	std::cout << std::endl << mstack;
	if (!mstack.empty())
		std::cout << CYN "top(): " DEF << mstack.top() << std::endl;
	std::cout << CYN "size(): " DEF << mstack.size() << std::endl;

	for (int i = 0; i < rem && !mstack.empty(); i++)
		mstack.pop();
	mstack.push(rand() % 100);
	
	std::cout << "\n-- removed " << rem << " elems and added an elem\n";
	std::cout << std::endl << mstack;
	if (!mstack.empty())
		std::cout << CYN "top(): " DEF << mstack.top() << std::endl;
	std::cout << CYN "size(): " DEF << mstack.size() << std::endl;

	std::cout << "\n-- copying onto a new stack\n";
	MutantStack<int> new_stack(mstack);
	if (!mstack.empty())
		std::cout << CYN "top(): " DEF << mstack.top() << std::endl;
	std::cout << CYN "size(): " DEF << mstack.size() << std::endl;

	std::cout << "\n-- testing iterators\n";
	MutantStack<int>::iterator it = new_stack.begin();
	MutantStack<int>::iterator ite = new_stack.end();
	std::cout << CYN "begin(): " DEF << *it << CYN " end() - 1: " DEF << *(ite - 1) << std::endl;
	MutantStack<int>::const_iterator cit = new_stack.cbegin();
	MutantStack<int>::const_iterator cite = new_stack.cend();
	std::cout << CYN "cbegin(): " DEF << *cit << CYN " cend() - 1: " DEF << *(cite - 1) << std::endl;
	MutantStack<int>::reverse_iterator rit = new_stack.rbegin();
	MutantStack<int>::reverse_iterator rite = new_stack.rend();
	std::cout << CYN "rbegin(): " DEF << *rit << CYN " rend() - 1: " DEF << *(rite - 1) << std::endl;
	MutantStack<int>::const_reverse_iterator crit = new_stack.crbegin();
	MutantStack<int>::const_reverse_iterator crite = new_stack.crend();
	std::cout << CYN "crbegin(): " DEF << *crit << CYN " crend() - 1: " DEF << *(crite - 1) << std::endl;
	std::cout << std::endl;
	
	return (0);
}
