#include "../inc/Span.hpp"

Span::Span(void) : N(1)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

Span::Span(unsigned int n): N(n)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

Span::Span(Span const &source)
{
	*this = source;
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UYEL "has been copy created" DEF << std::endl;
}

Span::~Span(void)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << URED "has been deleted" DEF << std::endl;
}

Span &Span::operator=(Span const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
	{
		N = source.N;
	}
	return (*this);
}

void Span::addNumber(int nbr)
{
	if (_span.size() == N)
		throw (std::out_of_range("couldn't add due to range limit"));
	_span.push_back(nbr);
}

void Span::addRange(int nbrs)
{
	if (_span.size() == N)
		throw (std::out_of_range("couldn't add due to range limit"));
	_span.push_back(nbrs);
}

int Span::shortestSpan(void) const
{
	return (1);
}

int Span::longestSpan(void) const
{
	return (1);
}

int_vec_t Span::get_span(void) const
{
	return (_span);
}

std::ostream &operator<<(std::ostream &out, Span const &source)
{
	int idx = 1;

	int_vec_t span = source.get_span();
	for (int_vec_t::iterator i = span.begin(); i != span.end(); i++)
		out << BLU "elem " << idx++ << ": " DEF << *i << std::endl;
	out << std::endl;
	return (out);
}
