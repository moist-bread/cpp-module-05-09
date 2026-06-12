#include "../inc/RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(RPN const &source)
{
	*this = source;
}

RPN::~RPN(void) {}

RPN &RPN::operator=(RPN const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

void RPN::convert(std::string input)
{
	std::cout << "RPN in process... " << input << std::endl;
}
