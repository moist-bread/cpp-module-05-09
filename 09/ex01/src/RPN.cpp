#include "../inc/RPN.hpp"

#include <iostream>
#include <ctype.h> // isdigit
#include <algorithm> // count

std::stack<int> RPN::_nums;
const char *RPN::_operators = "+-/*";
const short RPN::_amount_op = 4;

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

void RPN::process_expression(std::string exp)
{
	std::cout << "RPN processing the following expression: " << exp << std::endl;

	while (!RPN::_nums.empty())
		RPN::_nums.pop();

	while (!exp.empty())
	{
		if (std::isdigit(exp.at(0)))
			RPN::_nums.push(exp.at(0) - '0');
		else if (std::count(RPN::_operators, RPN::_operators + RPN::_amount_op, exp.at(0)))
			RPN::operation(exp.at(0));
		else
			throw(std::runtime_error("invalid character in expression"));
		
		if (DEBUG)
			std::cout << "processed... " << exp.at(0) << std::endl; 
		exp.erase(0, 1);
		
		if (!exp.empty())
		{
			if (exp.at(0) == ' ')
				exp.erase(0, 1);
			else if (std::isdigit(exp.at(0)))
				throw(std::runtime_error("invalid number in expression"));
			else
				throw(std::runtime_error("invalid character in expression"));
		}
	}

	if (RPN::_nums.size() > 1)
		throw(std::runtime_error("not enough operators"));
	else if (RPN::_nums.size() < 1)
		throw(std::runtime_error("not enough numbers"));

	std::cout << "result = " << RPN::_nums.top() << std::endl;
}

#include <limits>

void RPN::operation(const char &op)
{
	if (RPN::_nums.size() < 2)
		throw(std::runtime_error("not enough numbers to operate on"));

	long result = 0;
	long y = static_cast<long>(RPN::_nums.top());
	RPN::_nums.pop();
	long x = static_cast<long>(RPN::_nums.top());
	RPN::_nums.pop();

	switch (op)
	{
	case '+':
		result = x + y;
		break;
	case '-':
		result = x - y;
		break;
	case '/':
		if (y == 0)
			throw(std::runtime_error("division by 0"));
		result = x / y;
		break;
	case '*':
		result = x * y;
		break;
	default:
		throw(std::runtime_error("invalid character in expression"));
	}

	if (result < static_cast<long>(std::numeric_limits<int>::min()) || result > static_cast<long>(std::numeric_limits<int>::max()))
		throw(std::runtime_error("int overflowed during operations"));

	RPN::_nums.push(static_cast<int>(result));
}
