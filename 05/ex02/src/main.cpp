/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:01:53 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/02 15:03:20 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "../inc/Bureaucrat.hpp"
#include "../inc/AForm.hpp"

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade);
AForm *try_catch_form(const std::string &name, int grade_to_sign, int grade_to_exe);
void	try_catch_func(Bureaucrat *bureaucrat, void (Bureaucrat::*func)());

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   FORM UP, MAGGOTS! 🤑💰";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 3)
		return (std::cout << "usage: ./maggots [grade to sign] [grade to execute]" << std::endl, 2);
	
	int num_1 = std::atoi(av[1]);
	int num_2 = std::atoi(av[2]);
	
	AForm *license = try_catch_form("license", num_1, num_2);
	if (!license)
		return (1);
	std::cout << std::endl << std::endl;
	
	AForm *warranty = try_catch_form("warranty", num_1 - 1, num_2 - 1);
	if (!warranty)
		return (delete license, 1);
	std::cout << std::endl << std::endl;
	
	Bureaucrat *a = try_catch_bureaucrat("first guy", num_2);
	if (a)
	{
		a->signForm(*license);
		a->signForm(*warranty);
		delete a;
		std::cout << std::endl << std::endl;
	}
	
	Bureaucrat *b = try_catch_bureaucrat("second guy", num_1);
	if (b)
	{
		b->signForm(*license);
		b->signForm(*warranty);
		delete b;
		std::cout << std::endl << std::endl;
	}
	
	delete license;
	delete warranty;
	return (0);
}

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade)
{
	std::cout << BLU "try-catch with Bureaucrat name [" << name << "] and grade [" << grade << "]";
	std::cout << DEF << std::endl;
	try
	{
		Bureaucrat *bureaucrat = new Bureaucrat(name, grade);
		std::cout << "(didn't get thrown)" << std::endl;
		return (bureaucrat);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (NULL);
}

AForm *try_catch_form(const std::string &name, int grade_to_sign, int grade_to_exe)
{
	std::cout << BLU "try-catch with Form name [" << name << "], grade_to_sign [" << grade_to_sign << "] and grade_to_exe [" << grade_to_exe << "]";
	std::cout << DEF << std::endl;
	try
	{
		AForm *form = new AForm(name, grade_to_sign, grade_to_exe);
		std::cout << "(didn't get thrown)" << std::endl;
		return (form);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (NULL);
}

void	try_catch_func(Bureaucrat *bureaucrat, void (Bureaucrat::*func)())
{
	try
	{
		(bureaucrat->*func)();
		std::cout << "(didn't get thrown)" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
