/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AForm.hpp"

AForm::AForm(void) : _name("Nameless"), _signed(false), _grade_to_sign(150), _grade_to_execute(150)
{
	std::cout << GRN "the ";
	std::cout << *this;
	std::cout << " " UCYN "has been printed";
	std::cout << DEF << std::endl;
}

AForm::AForm(const std::string &name, int grade_to_sign, int grade_to_exe) : _name(name),  _signed(false), _grade_to_sign(grade_to_sign), _grade_to_execute(grade_to_exe)
{
	if (_grade_to_sign < 1 || _grade_to_execute < 1)
		throw(GradeTooHighException());
	if (_grade_to_sign > 150 || _grade_to_execute > 150)
		throw(GradeTooLowException());
	std::cout << GRN "the ";
	std::cout << *this;
	std::cout << " " UCYN "has been printed";
	std::cout << DEF << std::endl;
}

AForm::AForm(AForm const &source) : _name(source.get_name()), _grade_to_sign(source.get_grade_to_sign()),  _grade_to_execute(source.get_grade_to_execute())
{
	*this = source;
	std::cout << GRN "the ";
	std::cout << *this;
	std::cout << " " UYEL "has been scanned and copied";
	std::cout << DEF << std::endl;
}

AForm::~AForm(void)
{
	std::cout << GRN "the ";
	std::cout << *this;
	std::cout << " " URED "has been shredded";
	std::cout << DEF << std::endl;
}

AForm &AForm::operator=(AForm const &source)
{
	if (this != &source)
		_signed = source.get_signed();
	return (*this);
}

std::string AForm::get_name(void) const
{
	return (_name);
}

bool AForm::get_signed(void) const
{
	return (_signed);
}

int AForm::get_grade_to_sign(void) const
{
	return (_grade_to_sign);
}

int AForm::get_grade_to_execute(void) const
{
	return (_grade_to_execute);
}

void AForm::beSigned(Bureaucrat &source)
{
	if (source.getGrade() <= _grade_to_sign)
	{
		_signed = true;	
		std::cout << GRN "AForm [ " << _name << " ] is now signed ☑";
		std::cout << DEF << std::endl;
	}
	else
		throw(GradeTooLowException());
}

const char *AForm::GradeTooHighException::what(void) const throw()
{
	return ("grade too high");
}

const char *AForm::GradeTooLowException::what(void) const throw()
{
	return ("grade too low");
}

std::ostream &operator<<(std::ostream &out, AForm const &source)
{
	out << "AForm [ " << source.get_name() << " ]";
	if (source.get_signed())
		out << " signed ☑";
	else
		out << " not signed ☒";
	out << ", grade to sign [ " << source.get_grade_to_sign() << " ]";
	out << ", grade to execute [ " << source.get_grade_to_execute() << " ]";
	return (out);
}
