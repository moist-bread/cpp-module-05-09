/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:22:35 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/03 13:57:51 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//-‵,┊ needed libs by class
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
class AForm;

// -->┊( INTERN )┊.´-★☆★

class Intern
{
public:
	Intern(void); // default constructor
	Intern(Intern const &source); // copy constructor
	virtual ~Intern(void);		  // destructor

	Intern &operator=(Intern const &source); // copy assignment operator overload

	AForm *makeForm(std::string &form_name, std::string &form_target) const;
};
