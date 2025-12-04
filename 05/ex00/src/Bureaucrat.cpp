/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("Nameless"), _grade(150)
{
	std::cout << GRN "the Bureaucrat [ ";
	std::cout << getName() << " ] ";
	std::cout << "and grade [ ";
	std::cout << getGrade() << " ] ";
	std::cout << UCYN "has been born";
	std::cout << DEF << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade)
{
	if (_grade < 1)
		throw(GradeTooHighException());
	if (_grade > 150)
		throw(GradeTooLowException());
	std::cout << GRN "the Bureaucrat [ ";
	std::cout << getName() << " ] ";
	std::cout << "and grade [ ";
	std::cout << getGrade() << " ] ";
	std::cout << UCYN "has been born";
	std::cout << DEF << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &source)
{
	*this = source;
	std::cout << GRN "the Bureaucrat [ ";
	std::cout << getName() << " ] ";
	std::cout << "and grade [ ";
	std::cout << getGrade() << " ] ";
	std::cout << UYEL "has been copy cloned";
	std::cout << DEF << std::endl;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << GRN "the Bureaucrat [ ";
	std::cout << getName() << " ] ";
	std::cout << "and grade [ ";
	std::cout << getGrade() << " ] ";
	std::cout << URED "has died";
	std::cout << DEF << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &source)
{
	std::cout << YEL "copy assignment operator overload has been called";
	std::cout << DEF << std::endl;
	if (this != &source)
		_grade = source.getGrade();
	return (*this);
}

std::string Bureaucrat::getName(void) const
{
	return (_name);
}

int Bureaucrat::getGrade(void) const
{
	return (_grade);
}

void Bureaucrat::increment_grade(void)
{
	std::cout << "increment: ";
	_grade--;
	if (_grade < 1)
		throw(GradeTooHighException());
}

void Bureaucrat::decrement_grade(void)
{
	std::cout << "decrement: ";
	_grade++;
	if (_grade > 150)
		throw(GradeTooLowException());
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("high grade");
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("low grade");
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &source)
{
	out << BLU << source.getName() << DEF ", bureaucrat grade ";
	out << BLU <<  source.getGrade() << DEF ".";
	out << DEF << std::endl;
	return (out);
}
