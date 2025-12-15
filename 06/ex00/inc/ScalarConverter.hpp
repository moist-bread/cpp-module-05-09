/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:22:35 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/11 11:44:50 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <stdlib.h>

//-‵,┊ color defines

#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( DEFINES )┊.´-★☆★

/// @brief flags for input types
typedef enum s_type
{
	INVALID,
	CHAR,
	PSEUDO,
	INT,
	FLOAT,
	DOUBLE
} t_type;

// -->┊( SCALAR CONVERTER )┊.´-★☆★

class ScalarConverter
{
public:
	static void convert(std::string input);

private:
	ScalarConverter(void);	// default constructor
	ScalarConverter(ScalarConverter const &source);	// copy constructor
	~ScalarConverter(void);	// destructor
	ScalarConverter &operator=(ScalarConverter const &source);	// copy assignment operator overload
};
