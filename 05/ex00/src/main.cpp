/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:01:53 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/02 14:35:31 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include "../inc/Bureaucrat.hpp"

Bureaucrat *try_catch_bureaucrat(const std::string &name, int grade);
void	try_catch_func(Bureaucrat *bureaucrat, void (Bureaucrat::*func)());

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   FORM UP, MAGGOTS! 🤑💰";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./maggots [grade]" << std::endl, 2);
	int num = std::atoi(av[1]);
	Bureaucrat *a = try_catch_bureaucrat("first guy", num);
	if (a)
	{
		std::cout << *a << std::endl;
		try_catch_func(a, &Bureaucrat::decrement_grade);
		try_catch_func(a, &Bureaucrat::decrement_grade);
		try_catch_func(a, &Bureaucrat::decrement_grade);
		try_catch_func(a, &Bureaucrat::decrement_grade);
		try_catch_func(a, &Bureaucrat::decrement_grade);
		std::cout << *a << std::endl;
		delete a;
		std::cout << std::endl << std::endl;
	}
	Bureaucrat *b = try_catch_bureaucrat("second guy", num);
	if (b)
	{
		std::cout << *b << std::endl;
		try_catch_func(a, &Bureaucrat::increment_grade);
		try_catch_func(a, &Bureaucrat::increment_grade);
		try_catch_func(a, &Bureaucrat::increment_grade);
		try_catch_func(a, &Bureaucrat::increment_grade);
		try_catch_func(a, &Bureaucrat::increment_grade);
		std::cout << *b << std::endl;
		delete b;
		std::cout << std::endl << std::endl;
	}
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
