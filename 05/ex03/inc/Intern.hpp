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
	Intern(void);				  // default constructor
	Intern(Intern const &source); // copy constructor
	virtual ~Intern(void);		  // destructor

	Intern &operator=(Intern const &source); // copy assignment operator overload

	AForm *makeForm(std::string &form_name, std::string &form_target) const;
};
