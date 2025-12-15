#include <cstdlib>
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade);
AForm *try_catch_multi_form(const std::string &form_type, const std::string &target);

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   NO, YOU NEED FORM 28B NOT 28C... 🤑💰";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 5)
	{
		std::cout << "usage: ./28b [form type =(tree, robot, president)] [form target]" << std::endl;
		std::cout << "[signer bureaucrat grade] [executer bureaucrat grade]" << std::endl;
		return (2);
	}

	std::string form_type = av[1];
	std::string target = av[2];
	int sign_grade = std::atoi(av[3]);
	int exe_grade = std::atoi(av[4]);

	AForm *form = try_catch_multi_form(form_type, target);
	if (!form)
		return (1);
	std::cout << std::endl;

	Bureaucrat *a = try_catch_bureaucrat("guy that signs", sign_grade);
	if (a)
	{
		std::cout << std::endl;
		a->signForm(*form);
		delete a;
		std::cout << std::endl << std::endl;
	}

	Bureaucrat *b = try_catch_bureaucrat("guy that executes", exe_grade);
	if (b)
	{
		std::cout << std::endl;
		b->executeForm(*form);
		std::cout << std::endl;
		delete b;
		std::cout << std::endl << std::endl;
	}

	delete form;
	return (0);
}

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade)
{
	std::cout << UBLU "try-catch w/ Bureaucrat name [" << name << "] and grade [" << grade << "]";
	std::cout << DEF << std::endl
			  << std::endl;
	try
	{
		Bureaucrat *bureaucrat = new Bureaucrat(name, grade);
		std::cout << "(didn't get thrown)" << std::endl;
		return (bureaucrat);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (NULL);
}

AForm *try_catch_multi_form(const std::string &form_type, const std::string &target)
{
	std::cout << UBLU "try-catch multi form of type [" << form_type << "], target [" << target << "]";
	std::cout << DEF << std::endl
			  << std::endl;
	try
	{
		std::string types[3] = {"tree", "robot", "president"};

		int i = -1;
		while (++i < 3)
			if (form_type == types[i])
				break;
		AForm *form;
		switch (i)
		{
		case 0:
			form = new ShrubberyCreationForm(target);
			break;
		case 1:
			form = new RobotomyRequestForm(target);
			break;
		case 2:
			form = new PresidentialPardonForm(target);
			break;
		default:
			std::cout << "invalid type..." << std::endl;
			form = NULL;
			break;
		}
		return (form);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (NULL);
}
