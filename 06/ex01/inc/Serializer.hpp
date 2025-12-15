#pragma once

//-‵,┊ needed libs by class
#include <iostream>
#include <stdint.h>
#include <string>

//-‵,┊ struct defines

struct Data
{
	std::string str;
};

//-‵,┊ color defines

#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define CYN "\e[0;36m"
#define DEF "\e[0m"

// -->┊( SERIALIZER )┊.´-★☆★

class Serializer
{
public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);

private:
	Serializer(void);	// default constructor
	Serializer(Serializer const &source);	// copy constructor
	~Serializer(void);	// destructor
	Serializer &operator=(Serializer const &source);	// copy assignment operator overload
};
