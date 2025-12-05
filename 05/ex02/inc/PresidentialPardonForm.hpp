/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                          :+:      :+:    :+:   */
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

// -->┊( ROBOTOMY REQUEST FORM )┊.´-★☆★

class PresidentialPardonForm : public AForm
{
public:
    PresidentialPardonForm(void); // default constructor
    PresidentialPardonForm(const std::string &target);
    PresidentialPardonForm(PresidentialPardonForm const &source); // copy constructor
    virtual ~PresidentialPardonForm(void);                     // destructor

    PresidentialPardonForm &operator=(PresidentialPardonForm const &source); // copy assignment operator overload

    void execute(Bureaucrat const &executor) const;
};

std::ostream &operator<<(std::ostream &out, PresidentialPardonForm const &source);