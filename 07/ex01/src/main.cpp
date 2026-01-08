#include "../inc/iter.hpp"
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

	std::cout << BLU "testing iter print with a const int array" DEF << std::endl;
	
	const int const_int_array[5] = {6,7,8,9,10};
	::iter(const_int_array, 5, &::printer);
	std::cout << std::endl << std::endl;

	if (ac == 1)
		return (0);
	std::cout << BLU "testing iter print/inc with a char array" DEF << std::endl;
	
	char *char_array = av[1];
	unsigned int len = strlen(av[1]);

	::iter(char_array, len, &::printer);
	std::cout << std::endl;
	::iter(char_array, len, &::inc);
	std::cout << std::endl;
	::iter(char_array, len, &::printer);
	std::cout << std::endl;

	return (0);
}
