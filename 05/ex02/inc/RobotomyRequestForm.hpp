#pragma once

//-‵,┊ needed libs by class
#include "AForm.hpp"
#include <stdlib.h>
#include <time.h>

// -->┊( ROBOTOMY REQUEST FORM )┊.´-★☆★

class RobotomyRequestForm : public AForm
{
public:
    RobotomyRequestForm(void); // default constructor
    RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(RobotomyRequestForm const &source); // copy constructor
    virtual ~RobotomyRequestForm(void);                     // destructor

    RobotomyRequestForm &operator=(RobotomyRequestForm const &source); // copy assignment operator overload

    void execute(Bureaucrat const &executor) const;
};

std::ostream &operator<<(std::ostream &out, RobotomyRequestForm const &source);