#include "../inc/Array.hpp"
#include "../inc/Array.tpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VAL 7

int main()
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   ARRAY 🧢👣";
	std::cout << DEF << std::endl << std::endl;


    std::cout << BLU "creating the Arrays to test on"  DEF << std::endl;
	Array<int> numbers(MAX_VAL);

    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
	std::cout << std::endl << std::endl;
    
    // DIFFERENT SCOPE
    std::cout << BLU "testing copy assign and copy constructor" DEF << std::endl;
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
        for (int i = 0; i < MAX_VAL; i++)
        {
            std::cout << tmp[i] << " ";
            std::cout << test[i] << std::endl;
        }
    }
	std::cout << std::endl << std::endl;

    std::cout << BLU "checking if they're the same" DEF << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
    {
        std::cout << numbers[i] << " ";
        std::cout << mirror[i] << std::endl;
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
	std::cout << std::endl << std::endl;

    std::cout << BLU "testing the subscript [] operator" DEF << std::endl;
    try
    {
        numbers[-2] = 0;
        std::cout << GRN << "SUCCESS: " <<  numbers[-2] << DEF << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << RED << e.what() << DEF << std::endl;
    }
    try
    {
        numbers[MAX_VAL] = 0;
        std::cout << GRN << "SUCCESS: " <<  numbers[MAX_VAL] << DEF << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << RED << e.what() << DEF << std::endl;
    }
    try
    {
        numbers[0] = 0;
        std::cout << GRN << "SUCCESS: " <<  numbers[0] << DEF << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << RED << e.what() << DEF << std::endl;
    }
	std::cout << std::endl << std::endl;

    delete [] mirror;

	return (0);
}
