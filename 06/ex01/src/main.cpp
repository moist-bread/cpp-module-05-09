/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:01:53 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/12/11 19:00:27 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"

int main(int ac, char **av)
{
	std::cout << std::endl;
	std::cout << CYN ">>┈┈┈>   SERIALIZATION 🔜🔎";
	std::cout << DEF << std::endl << std::endl;

	if (ac != 2)
		return (std::cout << "usage: ./serialization [input]" << std::endl, 2);

	Data *data_ptr;
	data_ptr = new Data;
	data_ptr->str = av[1];
	
	uintptr_t serial = Serializer::serialize(data_ptr);
	Data * deserial = Serializer::deserialize(serial);
	
	std::cout << "original Data* ptr:	" << data_ptr << std::endl;
	std::cout << "serialized version:	" << serial << std::endl;
	std::cout << "deserialized version:	" << deserial << std::endl;
	std::cout << std::endl;
	
	std::cout << "acessing original data: '" << data_ptr->str << "'" << std::endl;
	std::cout << "acessing deserialized version: '" << deserial->str << "'" << std::endl;
	std::cout << std::endl;
	
	std::cout << "comparison between original and deserialized:	" << std::endl;
	if (data_ptr == deserial)
		std::cout << GRN "- they are equal" << std::endl;
	else	
		std::cout << YEL "- they are different" << std::endl;
	
	delete data_ptr;
	return (0);
}
