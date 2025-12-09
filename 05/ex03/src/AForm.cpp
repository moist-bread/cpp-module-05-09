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
	std::cout << GRN "an AForm ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
}

AForm::AForm(const std::string &name, int grade_to_sign, int grade_to_exe) : _name(name), _signed(false), _grade_to_sign(grade_to_sign), _grade_to_execute(grade_to_exe)
{
	if (_grade_to_sign < 1 || _grade_to_execute < 1)
		throw(GradeTooHighException());
	if (_grade_to_sign > 150 || _grade_to_execute > 150)
		throw(GradeTooLowException());
	std::cout << GRN "an AForm ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
}

AForm::AForm(AForm const &source) : _name(source.get_name()), _grade_to_sign(source.get_grade_to_sign()), _grade_to_execute(source.get_grade_to_execute())
{
	*this = source;
	std::cout << GRN "an AForm ";
	std::cout << UYEL "has been scanned and copied" DEF << std::endl;
}

AForm::~AForm(void)
{
	std::cout << GRN "an AForm ";
	std::cout << URED "has been shredded" DEF << std::endl;
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

std::string AForm::get_target(void) const
{
	return (_target);
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

const char *AForm::FormNotSignedException::what(void) const throw()
{
	return ("form not signed");
}

std::ostream &operator<<(std::ostream &out, AForm const &source)
{
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << "╵   " << "AForm: " << source.get_name() << std::endl;
	if (source.get_signed())
		out << "╵   " GRN "signed ☑" DEF << std::endl;
	else
		out << "╵   " RED "not signed ☒" DEF << std::endl;
	out << "╵   " YEL "▖ GRADE TO SIGN: " DEF << source.get_grade_to_sign();
	out << "   " BLU "▖ GRADE TO EXE: " DEF << source.get_grade_to_execute() << std::endl;
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << std::endl;

	return (out);
}
