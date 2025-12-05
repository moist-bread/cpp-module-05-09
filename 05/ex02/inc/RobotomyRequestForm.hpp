/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:22:35 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/05 16:11:21 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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