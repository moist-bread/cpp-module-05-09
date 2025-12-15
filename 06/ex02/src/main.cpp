#include "../inc/Base.hpp"
#include "../inc/ABC.hpp"

Base * generate(void);
void identify(Base* p);
void identify(Base& p);


int main()
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   IDENTIFY REAL TYPE 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	Base *thing = generate();
	Base &reskin = *thing;
	identify(thing);
	identify(reskin);

	delete thing;
	return (0);
}
