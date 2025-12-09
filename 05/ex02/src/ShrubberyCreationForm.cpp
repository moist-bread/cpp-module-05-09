/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm", 145, 137)
{
	_target = "default";
	std::cout << GRN "a ShrubberyCreationForm ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
	std::cout << *this;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", 145, 137)
{
	_target = target;
	std::cout << GRN "a ShrubberyCreationForm ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
	std::cout << *this;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &source) : AForm(source)
{
	*this = source;
	std::cout << GRN "a ShrubberyCreationForm ";
	std::cout << UYEL "has been scanned and copied" DEF << std::endl;
	std::cout << *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << GRN "a ShrubberyCreationForm ";
	std::cout << URED "has been shredded" DEF << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &source)
{
	if (this != &source)
		_target = source.get_signed();
	return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!this->get_signed())
	{
		throw(FormNotSignedException());
	}
	if (executor.getGrade() > this->get_grade_to_execute())
	{
		throw(GradeTooLowException());
	}

	std::string path = _target + "_shrubbery";
	std::ofstream output(path.c_str());

	if (!output.is_open())
	{
		std::cerr << "error in opening file during the execution of " << this->get_name() << std::endl;
		return;
	}
	output << ASCIITREE << std::endl;
	output.close();

	std::cout << executor.getName() << GRN " has executed " << this->get_name() << std::endl;
	std::cout << DEF "↳  the shrubbery has been created at " GRN << path;
	std::cout << DEF << std::endl;
}

std::ostream &operator<<(std::ostream &out, ShrubberyCreationForm const &source)
{
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << "╵   " << "Form: " << source.get_name() << std::endl;
	if (source.get_signed())
		out << "╵   " GRN "signed ☑" DEF << std::endl;
	else
		out << "╵   " RED "not signed ☒" DEF << std::endl;
	out << ":   " MAG "▖ TARGETTED AT: " DEF << source.get_target()<< std::endl;
	out << "╵   " YEL "▖ GRADE TO SIGN: " DEF << source.get_grade_to_sign();
	out << "   " BLU "▖ GRADE TO EXE: " DEF << source.get_grade_to_execute() << std::endl;
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << std::endl;

	return (out);
}
