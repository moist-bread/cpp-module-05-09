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
