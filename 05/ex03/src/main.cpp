#include <cstdlib>
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/Intern.hpp"

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade);

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   AT LEAST THIS BEATS COFFEE-MAKING 🤑💰";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 5)
	{
		std::cout << "usage: ./printer [form type =(tree, robot, president)] [form target]" << std::endl;
		std::cout << "[signer bureaucrat grade] [executer bureaucrat grade]" << std::endl;
		return (2);
	}
	
	std::string form_type = av[1];
	std::string target = av[2];
	int sign_grade = std::atoi(av[3]);
	int exe_grade = std::atoi(av[4]);
	
	Intern gerald;
	
	AForm *form = gerald.makeForm(form_type, target);
	if (!form)
		return (1);
	std::cout << std::endl << std::endl;
	
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
	std::cout << DEF << std::endl << std::endl;
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

// ./28b tree David 50 60
// ./28b tree David 50 600
// ./28b tree David 50 150
// ./28b robot Manu 1 1
// ./28b president Sergio 1 1
