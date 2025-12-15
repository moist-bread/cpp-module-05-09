/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:37:14 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/11/17 14:23:36 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"


Serializer::Serializer(void) {}

Serializer::Serializer(Serializer const &source)
{
	*this = source;
}

Serializer::~Serializer(void) {}

Serializer &Serializer::operator=(Serializer const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

uintptr_t Serializer::serialize(Data* ptr)
{
	uintptr_t serial = reinterpret_cast<uintptr_t>(ptr);
	return (serial);
}
Data* Serializer::deserialize(uintptr_t raw)
{
	Data *deserial = reinterpret_cast<Data *>(raw);
	return (deserial);
}
