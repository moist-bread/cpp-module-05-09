/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:22:35 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/05 17:17:32 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"
class Bureaucrat;

// -->┊( AFORM )┊.´-★☆★

class AForm
{
public:
	AForm(void); 							// default constructor
	AForm(const std::string &name, int grade_to_sign, int grade_to_exe);
	AForm(AForm const &source);				// copy constructor
	virtual ~AForm(void);					// destructor

	AForm &operator=(AForm const &source);	// copy assignment operator overload

	std::string get_name(void) const;
	bool get_signed(void) const;
	int get_grade_to_sign(void) const;
	int get_grade_to_execute(void) const;
    std::string get_target(void) const;

	void beSigned(Bureaucrat &source);
	virtual void execute(Bureaucrat const & executor) const = 0;
	
	class GradeTooHighException : public std::exception
	{
	public:
		const char *what(void) const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char *what(void) const throw();
	};

	class FormNotSignedException : public std::exception
	{
	public:
		const char *what(void) const throw();
	};

protected:
    std::string _target;
	
private:
	const std::string _name;
	bool _signed;
	const int _grade_to_sign;
	const int _grade_to_execute;
};

std::ostream &operator<<(std::ostream &out, AForm const &source);
