/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/09 10:58:03 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Intern.hpp"

Intern::Intern(void)
{
	std::cout << GRN "an Intern " UCYN "has been hired";
	std::cout << DEF << std::endl;
}

Intern::Intern(Intern const &source)
{
	*this = source;
	std::cout << GRN "an Intern " UYEL "has been cloned";
	std::cout << DEF << std::endl;
}

Intern::~Intern(void)
{
	std::cout << GRN "an Intern " URED "has been fired";
	std::cout << DEF << std::endl;
}

Intern &Intern::operator=(Intern const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

AForm *Intern::makeForm(std::string &form_name, std::string &form_target) const
{
	std::string types_short[3] = {"tree", "robot", "president"};
	std::string types_long[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	std::string types_together[3] = {"ShrubberyCreation", "RobotomyRequest", "PresidentialPardon"};
	
	int i = -1;
	while (++i < 3)
		if (form_name == types_short[i] || form_name == types_long[i] ||
			form_name == types_together[i])
			break;

	AForm *form;
	switch (i)
	{
	case 0:
		form = new ShrubberyCreationForm(form_target);
		break;
	case 1:
		form = new RobotomyRequestForm(form_target);
		break;
	case 2:
		form = new PresidentialPardonForm(form_target);
		break;
	default:
		std::cout << RED "an Intern can't print forms of type: " DEF << form_name << std::endl;
		return (NULL);
	}

	std::cout << GRN "an Intern has printed a Form of type: " DEF << form_name << std::endl;
	return (form);
}
