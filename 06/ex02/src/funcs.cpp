#include "../inc/Base.hpp"
#include "../inc/ABC.hpp"
#include <stdlib.h>
#include <time.h>

Base *generate(void)
{
	static int seed = false;
	if (seed == false)
	{
		srand(time(NULL));
		seed = true;
	}

	int type = rand() % 3;
	Base *base;
	switch (type)
	{
	case 0:
		base = new A;
		std::cout << "an A has been created" << std::endl;
		break;
	case 1:
		base = new B;
		std::cout << "a B has been created" << std::endl;
		break;
	case 2:
		base = new C;
		std::cout << "a C has been created" << std::endl;
		break;
	default:
		base = NULL;
	}
	return (base);
}

void identify(Base *p)
{
	std::string id;

	if (dynamic_cast<A*>(p))
		id = "A";
	else if (dynamic_cast<B*>(p))
		id = "B";
	else if (dynamic_cast<C*>(p))
		id = "C";
	else
		id = "None";

	std::cout << BLU "Base * has been identified as: " DEF;
	std::cout << id << " 🔎" << std::endl;
}

void identify(Base &p)
{
	std::string id;

	try
	{
        Base cast = dynamic_cast<A&>(p);
		id = "A";
    }
    catch (std::exception& e)
	{
        try
		{
			Base cast = dynamic_cast<B&>(p);
			id = "B";
		}
		catch (std::exception& e)
		{
			try
			{
				Base cast = dynamic_cast<C&>(p);
				id = "C";
			}
			catch (std::exception& e)
			{
				id = "None";
			}
		}
    }
	std::cout << BLU "Base & has been identified as: "	DEF;
	std::cout << id << " 🔎" << std::endl;
}
