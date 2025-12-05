/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:01:53 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/05 17:20:48 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "../inc/Bureaucrat.hpp"
#include "../inc/Form.hpp"

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade);
Form *try_catch_form(const std::string &name, int grade_to_sign, int grade_to_exe);
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
	
	Form *license = try_catch_form("license", num_1, num_2);
	if (!license)
		return (1);
	std::cout << std::endl << std::endl;
	
	Form *warranty = try_catch_form("warranty", num_1 - 1, num_2 - 1);
	if (!warranty)
		return (delete license, 1);
	std::cout << std::endl << std::endl;
	
	Bureaucrat *a = try_catch_bureaucrat("first guy", num_2);
	if (a)
	{
		std::cout << std::endl;
		a->signForm(*license);
		a->signForm(*warranty);
		delete a;
		std::cout << std::endl << std::endl;
	}
	
	Bureaucrat *b = try_catch_bureaucrat("second guy", num_1);
	if (b)
	{
		std::cout << std::endl;
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

Form *try_catch_form(const std::string &name, int grade_to_sign, int grade_to_exe)
{
	std::cout << UBLU "try-catch w/ Form name [" << name << "], sign grade [" << grade_to_sign << "] and exe grade [" << grade_to_exe << "]";
	std::cout << DEF << std::endl << std::endl;
	try
	{
		Form *form = new Form(name, grade_to_sign, grade_to_exe);
		std::cout << "(didn't get thrown)" << std::endl;
		return (form);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
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
		std::cerr << e.what() << std::endl;
	}
}
