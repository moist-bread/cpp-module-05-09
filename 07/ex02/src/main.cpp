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


    std::cout << "\n-- creating the Arrays to test on\n";
	Array<int> numbers(MAX_VAL);

    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand() % 100;
        numbers[i] = value;
        mirror[i] = value;
    }
    
    // DIFFERENT SCOPE
    std::cout << "\n\n-- testing copy assign and copy constructor\n";
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
        for (int i = 0; i < MAX_VAL; i++)
        {
            std::cout << tmp[i] << " ";
            std::cout << test[i] << std::endl;
        }
    }

    std::cout << "\n\n-- checking if they're the same\n";
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

    std::cout << "\n\n-- testing the subscript [] operator\n";
    int array[] = {-2, MAX_VAL, 0};
    for (int i = 0; i < 3; i++)
    {
        try
        {
            numbers[array[i]] = 0;
            std::cout << GRN << "success: " <<  numbers[array[i]] << DEF << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << RED << e.what() << DEF << std::endl;
        }
    }
   	std::cout << std::endl << std::endl;

    delete [] mirror;

	return (0);
}
