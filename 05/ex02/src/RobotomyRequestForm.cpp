/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) : AForm("RobotomyRequestForm", 72, 45)
{
	srand(time(NULL));
	_target = "default";
	std::cout << GRN "a RobotomyRequestForm ";
	std::cout << UCYN "has been printed...";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("RobotomyRequestForm", 72, 45)
{
	srand(time(NULL));
	_target = target;
	std::cout << GRN "a RobotomyRequestForm ";
	std::cout << UCYN "has been printed...";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &source) : AForm(source)
{
	srand(time(NULL));
	*this = source;
	std::cout << GRN "a RobotomyRequestForm ";
	std::cout << UYEL "has been scanned and copied";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << GRN "a RobotomyRequestForm ";
	std::cout << URED "has been shredded";
	std::cout << DEF << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &source)
{
	if (this != &source)
		_target = source.get_signed();
	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!this->get_signed())
	{
		throw(FormNotSignedException());
	}
	if (executor.getGrade() > this->get_grade_to_execute())
	{
		throw(GradeTooLowException());
	}

	int success = rand() % 2;
	
	std::cout << executor.getName() << GRN " has executed " << this->get_name() << std::endl;
	std::cout << BLU "BZZZZZZ BRRRRRRRRR HMMMMMMM *drilling sounds*" DEF << std::endl;
	if (success)
		std::cout << DEF "↳  " << _target << " has been " GRN "successfully robotomized";
	else
		std::cout << DEF "↳  unfortunatly the robotomy of " RED << _target << " failed";
	std::cout << DEF << std::endl;
}

std::ostream &operator<<(std::ostream &out, RobotomyRequestForm const &source)
{
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << "╵   " << "Form: " << source.get_name() << std::endl;
	if (source.get_signed())
		out << "╵   " GRN "signed ☑" DEF << std::endl;
	else
		out << "╵   " RED "not signed ☒" DEF << std::endl;
	out << ":   " MAG "▖ TARGETTED AT: " DEF << source.get_target() << std::endl;
	out << "╵   " YEL "▖ GRADE TO SIGN: " DEF << source.get_grade_to_sign();
	out << "   " BLU "▖ GRADE TO EXE: " DEF << source.get_grade_to_execute() << std::endl;
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << std::endl;

	return (out);
}
