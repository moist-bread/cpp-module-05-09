/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : AForm("PresidentialPardonForm", 25, 5)
{
	_target = "default";
	std::cout << GRN "a PresidentialPardonForm ";
	std::cout << UCYN "has been printed...";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("PresidentialPardonForm", 25, 5)
{
	_target = target;
	std::cout << GRN "a PresidentialPardonForm ";
	std::cout << UCYN "has been printed...";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &source) : AForm(source)
{
	*this = source;
	std::cout << GRN "a PresidentialPardonForm ";
	std::cout << UYEL "has been scanned and copied";
	std::cout << DEF << std::endl;
	std::cout << *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	std::cout << GRN "a PresidentialPardonForm ";
	std::cout << URED "has been shredded";
	std::cout << DEF << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &source)
{
	if (this != &source)
		_target = source.get_signed();
	return (*this);
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (!this->get_signed())
	{
		throw(FormNotSignedException());
	}
	if (executor.getGrade() > this->get_grade_to_execute())
	{
		throw(GradeTooLowException());
	}

	std::cout << executor.getName() << GRN " has executed " << this->get_name() << std::endl;
	std::cout << DEF "↳  " << _target << " has been pardoned by Zaphod Beeblebrox";
	std::cout << DEF << std::endl;
}

std::ostream &operator<<(std::ostream &out, PresidentialPardonForm const &source)
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
