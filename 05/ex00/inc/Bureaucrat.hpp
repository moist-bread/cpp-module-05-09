/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:22:35 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/28 15:47:22 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <exception>

//-‵,┊ color defines

#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"

#define URED "\e[4;31m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"

#define DEF "\e[0m"

// -->┊( BUREAUCRAT )┊.´-★☆★

class Bureaucrat
{
public:
	Bureaucrat(void); 						// default constructor
	Bureaucrat(const std::string &name, int grade);
	Bureaucrat(Bureaucrat const &source);	// copy constructor
	virtual ~Bureaucrat(void);				// destructor

	Bureaucrat &operator=(Bureaucrat const &source); // copy assignment operator overload

	std::string getName(void) const;
	int getGrade(void) const;

	void increment_grade(void);
	void decrement_grade(void);

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

private:
	const std::string _name;
	int _grade;
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &source);
