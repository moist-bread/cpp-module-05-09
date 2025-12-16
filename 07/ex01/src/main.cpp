#include "../inc/iter.hpp"
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   ITER 🧢👣";
	std::cout << DEF << std::endl << std::endl;

	std::cout << BLU "testing iter print/inc with an int array" DEF << std::endl;
	
	int int_array[5] = {1,2,3,4,5};
	::iter(int_array, 5, &::printer);
	std::cout << std::endl;
	::iter(int_array, 5, &::inc);
	std::cout << std::endl;
	::iter(int_array, 5, &::printer);
	std::cout << std::endl << std::endl;

	if (ac == 1)
		return (0);
	
	std::cout << BLU "testing iter print/inc with a char array" DEF << std::endl;
	
	char *char_array = av[1];
	int len = strlen(av[1]);

	::iter(char_array, len, &::printer);
	std::cout << std::endl;
	::iter(char_array, len, &::inc);
	std::cout << std::endl;
	::iter(char_array, len, &::printer);
	std::cout << std::endl;

	return (0);
}
