#include "../inc/ScalarConverter.hpp"

static t_type parse_type(std::string input);
static void inv_output(void);
static void char_output(char c);
static void pseudo_output(std::string input);
static void int_output(std::string input);
static void float_output(std::string input);
static void double_output(std::string input);

ScalarConverter::ScalarConverter(void) {}

ScalarConverter::ScalarConverter(ScalarConverter const &source)
{
	*this = source;
}

ScalarConverter::~ScalarConverter(void) {}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

void ScalarConverter::convert(std::string input)
{
	std::cout << "convertion in process..." << std::endl;
	std::cout << std::fixed << std::setprecision(1) << std::endl;

	t_type type = parse_type(input);

	switch (type)
	{
	case INVALID:
		inv_output();
		break;
	case CHAR:
		char_output(input.at(0));
		break;
	case PSEUDO:
		pseudo_output(input);
		break;
	case INT:
		int_output(input);
		break;
	case FLOAT:
		float_output(input);
		break;
	case DOUBLE:
		double_output(input);
		break;
	}
}

static t_type parse_type(std::string input)
{
	if (input.empty())
		return (INVALID);
	else if (input.length() == 1 && !isdigit(input.at(0)))
		return (CHAR);
	else if (input == "-inff" || input == "+inff" || input == "nanf" || input == "-inf" || input == "+inf" || input == "nan")
		return (PSEUDO);
	else if (input.find('.') == std::string::npos)
	{
		if (input.find_first_not_of("+-0123456789") != std::string::npos)
			return (INVALID);
		char* end = NULL;
		double value = std::strtod(input.c_str(), &end);
		if (*end || value == HUGE_VAL || value == -HUGE_VAL)
			return (INVALID);
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
			return (INVALID);
		return (INT);
	}
	else if (input.at(input.length() - 1) == 'f')
	{
		if (input.find_first_not_of("+-0123456789.f") != std::string::npos || input.length() < 4)
			return (INVALID);
		if (input.find_first_of("f") != input.find_last_of("f"))
			return (INVALID);
		char* end = NULL;
		double value = std::strtod(input.c_str(), &end);
		if (*end != 'f' || *(end - 1) == '.' || value == HUGE_VAL || value == -HUGE_VAL)
			return (INVALID);
		if (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max())
			return (INVALID);
		return (FLOAT);
	}
	else
	{
		if (input.find_first_not_of("+-0123456789.") != std::string::npos || input.length() < 3)
			return (INVALID);
		char* end = NULL;
		double value = std::strtod(input.c_str(), &end);
		if (*end || *(end - 1) == '.' || value == HUGE_VAL || value == -HUGE_VAL)
			return (INVALID);
		return (DOUBLE);
	}
}

static void inv_output(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

static void char_output(char c)
{
	if (isprint(c))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << std::endl;
}

static void pseudo_output(std::string input)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << input.substr(0, 4 - (input.at(0) == 'n')) << "f" << std::endl;
	std::cout << "double: " << input.substr(0, 4 - (input.at(0) == 'n')) << std::endl;
}

static void int_output(std::string input)
{
	int value = std::strtod(input.c_str(), NULL);
	
	if (value >= 0 && value <= 255 && isprint(value))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << value << std::endl;
	std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << std::endl;
}

static void float_output(std::string input)
{
	float value = std::strtod(input.c_str(), NULL);
	
	if (value >= 0 && value <= 255 && isprint(value))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	std::cout << "float: " << value << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << std::endl;
}

static void double_output(std::string input)
{
	double value = std::strtod(input.c_str(), NULL);
	
	if (value >= 0 && value <= 255 && isprint(value))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << value << std::endl;
}
