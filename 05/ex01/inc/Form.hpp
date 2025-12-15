#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"
class Bureaucrat;

// -->┊( FORM )┊.´-★☆★

class Form
{
public:
	Form(void); // default constructor
	Form(const std::string &name, int grade_to_sign, int grade_to_exe);
	Form(Form const &source); // copy constructor
	virtual ~Form(void);	  // destructor

	Form &operator=(Form const &source); // copy assignment operator overload

	std::string get_name(void) const;
	bool get_signed(void) const;
	int get_grade_to_sign(void) const;
	int get_grade_to_execute(void) const;

	void beSigned(Bureaucrat &source);

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
	bool _signed;
	const int _grade_to_sign;
	const int _grade_to_execute;
};

std::ostream &operator<<(std::ostream &out, Form const &source);
